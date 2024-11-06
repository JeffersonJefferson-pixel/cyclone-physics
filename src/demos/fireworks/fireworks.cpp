#include <cyclone/cyclone.h>
#include "../app.h"
#include "../timing.h"
#include "../ogl_headers.h"

static cyclone::Random crandom;

class Firework : public cyclone::Particle
{
public:
    unsigned type;

    /**
     * The age of firework determines when it detonates. Age gradually
     * decreases; when it reaches zero, the firework delivers its payload.
     */
    cyclone::real age;

    bool update(cyclone::real duration)
    {
        // update physcial state.
        integrate(duration);

        age -= duration;

        return (age < 0) || (position.y < 0);
    }
};

struct FireworkRule
{
    unsigned type;

    cyclone::real minAge;

    cyclone::real maxAge;

    cyclone::Vector3 minVelocity;
    cyclone::Vector3 maxVelocity;

    cyclone::real damping;

    struct Payload
    {
        unsigned type;

        unsigned count;

        void set(unsigned type, unsigned count)
        {
            Payload::type = type;
            Payload::count = count;
        }
    };

    unsigned payloadCount;

    Payload *payloads;

    FireworkRule() : payloadCount(0), payloads(NULL) {}

    void init(unsigned payloadCount)
    {
        FireworkRule::payloadCount = payloadCount;
        payloads = new Payload[payloadCount];
    }

    void setParameters(unsigned type, cyclone::real minAge, cyclone::real maxAge,
                       const cyclone::Vector3 &minVelocity, const cyclone::Vector3 &maxVelocity,
                       cyclone::real damping)
    {
        FireworkRule::type = type;
        FireworkRule::minAge = minAge;
        FireworkRule::maxAge = maxAge;
        FireworkRule::minVelocity = minVelocity;
        FireworkRule::maxVelocity = maxVelocity;
        FireworkRule::damping = damping;
    }

    void create(Firework *firework, const Firework *parent = NULL) const
    {
        firework->type = type;
        firework->age = crandom.randomReal(minAge, maxAge);

        cyclone::Vector3 vel;
        if (parent)
        {
            firework->setPosition(parent->getPosition());
            vel += parent->getVelocity();
        }
        else
        {
            cyclone::Vector3 start;
            int x = (int)crandom.randomInt(3) - 1;
            start.x = 0.5f * cyclone::real(x);
            firework->setPosition(start);
        }

        vel += crandom.randomVector(minVelocity, maxVelocity);
        firework->setVelocity(vel);

        firework->setMass(10);

        firework->setDamping(damping);
        
        firework->setAcceleration(cyclone::Vector3::GRAVITY);

        firework->clearAccumulator();
    }
};

class FireworksDemo : public Application
{
    const static unsigned maxFireworks = 1024;

    Firework fireworks[maxFireworks];

    const static unsigned ruleCount = 9;
    FireworkRule rules[ruleCount];

    unsigned nextFirework;

    void initFireworkRules();

    void create(unsigned type, const Firework *parent);

    void create(unsigned type, unsigned number, const Firework *parent);

    public:
        FireworksDemo();

        virtual void update();

        virtual void initGraphics();

        virtual const char* getTitle();

        virtual void display();

        virtual void key(unsigned char key);
};

FireworksDemo::FireworksDemo() : nextFirework(0)
{
    for (Firework *firework = fireworks; firework < fireworks + maxFireworks; firework ++) 
    {
        firework->type = 0;
    }

    initFireworkRules();
}

void FireworksDemo::initFireworkRules()
{
    rules[0].init(2);
    rules[0].setParameters(1, 0.5f, 1.4f, cyclone::Vector3(-5, 25, -5), cyclone::Vector3(5, 28, 5), 0.1);
    rules[0].payloads[0].set(3, 5);
    rules[0].payloads[1].set(5, 5);

    rules[1].init(1);
    rules[1].setParameters(2, 0.5f, 1.0f, cyclone::Vector3(-5, 10, -5), cyclone::Vector3(5, 20, 5), 0.8);
    rules[1].payloads[0].set(4, 2);

    rules[2].init(0);
    rules[2].setParameters(3, 0.5f, 1.5f, cyclone::Vector3(-5, -5, -5), cyclone::Vector3(5, 5, 5), 0.1);

     rules[3].init(0);
    rules[3].setParameters(
        4, // type
        0.25f, 0.5f, // age range
        cyclone::Vector3(-20, 5, -5), // min velocity
        cyclone::Vector3(20, 5, 5), // max velocity
        0.2 // damping
        );

    rules[4].init(1);
    rules[4].setParameters(
        5, // type
        0.5f, 1.0f, // age range
        cyclone::Vector3(-20, 2, -5), // min velocity
        cyclone::Vector3(20, 18, 5), // max velocity
        0.01 // damping
        );
    rules[4].payloads[0].set(3, 5);

    rules[5].init(0);
    rules[5].setParameters(
        6, // type
        3, 5, // age range
        cyclone::Vector3(-5, 5, -5), // min velocity
        cyclone::Vector3(5, 10, 5), // max velocity
        0.95 // damping
        );

    rules[6].init(1);
    rules[6].setParameters(
        7, // type
        4, 5, // age range
        cyclone::Vector3(-5, 50, -5), // min velocity
        cyclone::Vector3(5, 60, 5), // max velocity
        0.01 // damping
        );
    rules[6].payloads[0].set(8, 10);

    rules[7].init(0);
    rules[7].setParameters(
        8, // type
        0.25f, 0.5f, // age range
        cyclone::Vector3(-1, -1, -1), // min velocity
        cyclone::Vector3(1, 1, 1), // max velocity
        0.01 // damping
        );

    rules[8].init(0);
    rules[8].setParameters(
        9, // type
        3, 5, // age range
        cyclone::Vector3(-15, 10, -5), // min velocity
        cyclone::Vector3(15, 15, 5), // max velocity
        0.95 // damping
        );
}

void FireworksDemo::create(unsigned type, const Firework *parent)
{
    FireworkRule *rule = rules + (type - 1);

    rule->create(fireworks + nextFirework, parent);

    nextFirework = (nextFirework + 1) % maxFireworks;
}

void FireworksDemo::create(unsigned type, unsigned number, const Firework *parent)
{
    for (unsigned i = 0; i < number; i++)
    {
        create(type, parent);
    }
}

void FireworksDemo::initGraphics()
{
    Application::initGraphics();

    glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
}

const char* FireworksDemo::getTitle() 
{
    return "Cyclone > Fireworks Demo";
}

void FireworksDemo::update()
{
    float duration = (float)TimingData::get().lastFrameDuration * 0.001f;
    if (duration <= 0.0f) return;

    for (Firework *firework = fireworks; firework < fireworks + maxFireworks; firework++)
    {
        if (firework->type > 0)
        {
            if (firework->update(duration))
            {
                FireworkRule *rule = rules + (firework->type - 1);
                
                firework->type = 0;

                for (unsigned i = 0; i < rule->payloadCount; i++)
                {
                    FireworkRule::Payload *payload = rule->payloads + i;
                    create(payload->type, payload->count, firework);
                }
            }
        }
    }

    Application::update();
}

void FireworksDemo::display() 
{
    const static cyclone::real size = 0.1f;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 4.0, 10.0, 0.0, 4.0, 0.0, 0.0, 1.0, 0.0);

    glBegin(GL_QUADS);
    for (Firework *firework = fireworks; firework < fireworks+maxFireworks; firework++)
    {
        if (firework->type > 0)
        {
            switch (firework->type) 
            {
                case 1: glColor3f(1, 0, 0); break;
                case 2: glColor3f(1,0.5f,0); break;
                case 3: glColor3f(1,1,0); break;
                case 4: glColor3f(0,1,0); break;
                case 5: glColor3f(0,1,1); break;
                case 6: glColor3f(0.4f,0.4f,1); break;
                case 7: glColor3f(1,0,1); break;
                case 8: glColor3f(1,1,1); break;
                case 9: glColor3f(1,0.5f,0.5f); break;
            };

            const cyclone::Vector3 &pos = firework->getPosition();
            glVertex3f(pos.x-size, pos.y - size, pos.z);
            glVertex3f(pos.x + size, pos.y - size, pos.z);
            glVertex3f(pos.x + size, pos.y + size, pos.z);
            glVertex3f(pos.x - size, pos.y + size, pos.z);

            // firework reflection
            glVertex3f(pos.x-size, -pos.y - size, pos.z);
            glVertex3f(pos.x + size, -pos.y - size, pos.z);
            glVertex3f(pos.x + size, -pos.y + size, pos.z);
            glVertex3f(pos.x - size, -pos.y + size, pos.z);
        }
    }
    glEnd();
}

void FireworksDemo::key(unsigned char key)
{
    switch (key)
    {
        case '1': create(1, 1, NULL); break;
        case '2': create(2, 1, NULL); break;
        case '3': create(3, 1, NULL); break;
        case '4': create(4, 1, NULL); break;
        case '5': create(5, 1, NULL); break;
        case '6': create(6, 1, NULL); break;
        case '7': create(7, 1, NULL); break;
        case '8': create(8, 1, NULL); break;
        case '9': create(9, 1, NULL); break;
    }
}

Application* getApplication()
{
    return new FireworksDemo();
}