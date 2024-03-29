#include "Functions/RKDiscretizer.hpp"
#include <iostream>
namespace NBodyEnv{
    void RKDiscretizer::clear() {
        m_a.clear();
        m_b.clear();
        m_c.clear();
    }

    void RKDiscretizer::setFeuler() {
        clear();

        m_a.push_back({0.0});
        m_b.push_back(1.0);
        m_c.push_back(0.0);
    }

    void RKDiscretizer::setBeuler() {
        clear();

        m_a.push_back({1.0});
        m_b.push_back(1.0);
        m_c.push_back(1.0);
    }

    void RKDiscretizer::setRK4() {
        clear();

        m_a = {
            {0.0,       0.0,       0.0, 0.0},
            {1.0 / 2.0, 0.0,       0.0, 0.0},
            {0.0,       1.0 / 2.0, 0.0, 0.0},
            {0.0,       0.0,       1.0, 0.0}
        };
        m_b = {1.0 / 6.0, 1.0 / 3.0, 1.0 / 3.0, 1.0 / 6.0};
        m_c = {0.0, 1.0 / 2.0, 1.0 / 2.0, 1.0 };

    }

    void RKDiscretizer::setImpMid() {
        clear();

        m_a = {{1.0 / 2.0}};
        m_b = {1.0};
        m_c = {1.0 / 2.0};
    }

    void RKDiscretizer::setCrankNic() {
        clear();

        m_a = {
            {0.0,       0.0},
            {1.0 / 2.0, 1.0 / 2.0}
        };
        m_b = {1.0 / 2.0, 1.0 / 2.0};
        m_c = {0.0, 1.0};
    }
    
    void RKDiscretizer::setExpMid() {
        clear();

        m_a = {
            {0.0, 0.0},
            {1.0 / 2.0, 0.0}
        };
        m_b = {0.0, 1.0};
        m_c = {0.0, 1.0 / 2.0};
    }

    void RKDiscretizer::setHeun() {
        clear();

        m_a = {
            {0.0, 0.0},
            {1.0, 0.0}
        };
        m_b = {1.0 / 2.0, 1.0 / 2.0};
        m_c = {0.0, 1.0};
    }

    void RKDiscretizer::setRalston() {
        clear();

        m_a = {
            {0.0, 0.0},
            {2.0 / 3.0, 0.0}
        };
        m_b = {1.0 / 4.0, 3.0 / 4.0};
        m_c = {0.0, 2.0 / 3.0};
    }

    void RKDiscretizer::setKutta3() {
        clear();

        m_a = {
            {0.0, 0.0, 0.0},
            {1.0 / 2.0, 0.0, 0.0},
            {-1.0, 2.0, 0.0}
        };
        m_b = {1.0 / 6.0, 2.0 / 3.0, 1.0 / 6.0};
        m_c = {0.0, 1.0 / 2.0, 1.0};
    }

    void RKDiscretizer::setHeun3() {
        clear();

        m_a = {
            {0.0,       0.0,       0.0},
            {1.0 / 3.0, 0.0,       0.0},
            {0.0,       2.0 / 3.0, 0.0}
        };
        m_b = {1.0 / 4.0, 0.0, 3.0 / 4.0};
        m_c = {0.0, 1.0 / 3.0, 2.0 / 3.0};
    }

    void RKDiscretizer::setWray3() {
        clear();

        m_a = {
            {0.0,        0.0,        0.0},
            {8.0 / 15.0, 0.0,        0.0},
            {1.0 / 4.0,  5.0 / 12.0, 0.0}
        };
        m_b = {1.0 / 4.0, 0.0, 3.0 / 4.0};
        m_c = {0.0, 8.0 / 15.0, 2.0 / 3.0};
    }

    void RKDiscretizer::setRalston3() {
        clear();

        m_a = {
            {0.0,       0.0,       0.0},
            {1.0 / 2.0, 0.0,       0.0},
            {0.0,       3.0 / 4.0, 0.0}
        };
        m_b = {2.0 / 9.0, 1.0 / 3.0, 4.0 / 9.0};
        m_c = {0.0, 1.0 / 2.0, 3.0 / 4.0};
    }

    void RKDiscretizer::setSSPRK3() {
        clear();

        m_a = {
            {0.0,       0.0,       0.0},
            {1.0,       0.0,       0.0},
            {1.0 / 4.0, 1.0 / 4.0, 0.0}
        };
        m_b = {1.0 / 6.0, 1.0 / 6.0, 2.0 / 3.0};
        m_c = {0.0, 1.0, 1.0 / 2.0};
    }

    void RKDiscretizer::setRK38() {
        clear();

        m_a = {
            {0.0,        0.0,  0.0, 0.0},
            {1.0 / 3.0,  0.0,  0.0, 0.0},
            {-1.0 / 3.0, 1.0,  0.0, 0.0},
            {1.0,        -1.0, 1.0, 0.0}
        };
        m_b = {1.0 / 8.0, 3.0 / 8.0, 3.0 / 8.0, 1.0 / 8.0};
        m_c = {0.0, 1.0 / 3.0, 2.0 / 3.0, 1.0};
    }

    void RKDiscretizer::setRalston4() {
        clear();

        m_a = {
            {0.0,        0.0,         0.0,        0.0},
            {0.4,        0.0,         0.0,        0.0},
            {0.29697761, 0.15875964,  0.0,        0.0},
            {0.21810040, -3.05096516, 3.83286476, 0.0}
        };

        m_b = {0.17476028, -0.55148066, 1.20553560, 0.17118478};
        m_c = {0.0, 0.4, 0.45573725, 1};
    }

    void RKDiscretizer::discretize(Particle &target, Particle &particleOne, Particle &particleTwo, std::function<Force(Pos &, Pos &, double, double, double, double)> func, double deltaTime){
        
        Pos tempPos;
        // Force force = {0.0, 0.0, 0.0};
        std::vector<Vel> k;
        Vel kSum;
        // Final vel
        Vel finalVel = {0.0, 0.0, 0.0};
        // Final pos
        Pos finalPos = {0.0, 0.0, 0.0};

        for(size_t i = 0; i < size(m_b); ++i) {

            // Reset tempPos value to original
            tempPos = particleOne.getValuePos();

            // Update time
            double newT = m_c[i] * deltaTime;



            // Calculate sum of previous K (velocity)
            kSum = {0.0, 0.0, 0.0};

            for(size_t j = 0; j < i; ++j) {
                kSum.xVel += m_a[i][j] * k[j].xVel;
                kSum.yVel += m_a[i][j] * k[j].yVel;
                kSum.zVel += m_a[i][j] * k[j].zVel;
            }

            // Compute new position
            tempPos.xPos += deltaTime * kSum.xVel;
            tempPos.yPos += deltaTime * kSum.yVel;
            tempPos.zPos += deltaTime * kSum.zVel;
            
            // Compute velocity (RK)
            kSum = discretizeVel(particleOne, particleTwo, func, newT);

            // Save k
            k.push_back(kSum);

            // Add contribute to final pos
            finalPos.xPos += deltaTime * m_b[i] * k[i].xVel;
            finalPos.yPos += deltaTime * m_b[i] * k[i].yVel;
            finalPos.zPos += deltaTime * m_b[i] * k[i].zVel;
        }

        // Get velocity discretization with the right time-step
        finalVel = discretizeVel(particleOne, particleTwo, func, deltaTime);
        
        // Save discretized
        target.setVel(finalVel);

        // Compute new position
        tempPos = {target.getPos().xPos, target.getPos().yPos, target.getPos().zPos};
        tempPos.xPos += finalPos.xPos;
        tempPos.yPos += finalPos.yPos;
        tempPos.zPos += finalPos.zPos;

        // Save new position
        target.setPos(tempPos);
    }

    Vel RKDiscretizer::discretizeVel(Particle &particleOne, Particle &particleTwo, std::function<Force(Pos &, Pos &, double, double, double, double)> func, double deltaTime){
        Pos tempPos;
        Pos particleTwoPos = particleTwo.getValuePos();
        Vel tempVel;
        Force force = {0.0, 0.0, 0.0};
        std::vector<Acc> k;
        Acc kSum;
        // Final vel
        Vel finalVel = {0.0, 0.0, 0.0};

        for(size_t i = 0; i < size(m_b); ++i) {

            // Reset tempPos value to original
            tempPos = particleOne.getValuePos();
            // Reset tempVel value to original
            tempVel = particleOne.getValueVel();

            // Update time
            double newT = m_c[i] * deltaTime;



            // Calculate sum of previous K
            kSum = {0.0, 0.0, 0.0};

            for(size_t j = 0; j < i; ++j) {
                kSum.xAcc += m_a[i][j] * k[j].xAcc;
                kSum.yAcc += m_a[i][j] * k[j].yAcc;
                kSum.zAcc += m_a[i][j] * k[j].zAcc;
            }

            // Compute new velocity
            tempVel.xVel += deltaTime * kSum.xAcc;
            tempVel.yVel += deltaTime * kSum.yAcc;
            tempVel.zVel += deltaTime * kSum.zAcc;

            // Update position
            tempPos.xPos += newT * tempVel.xVel;
            tempPos.yPos += newT * tempVel.yVel;
            tempPos.zPos += newT * tempVel.zVel;

            // Compute Force
            force = func(tempPos, particleTwoPos, particleOne.getSpecInfo(), particleTwo.getSpecInfo(), particleOne.getRadius(), particleTwo.getRadius());
            
            // Compute K (Acceleration)
            kSum.xAcc = force.xForce / particleOne.getSpecInfo();
            kSum.yAcc = force.yForce / particleOne.getSpecInfo();
            kSum.zAcc = force.zForce / particleOne.getSpecInfo();

            // Save k
            k.push_back(kSum);

            // Add contribute to final vel
            finalVel.xVel += deltaTime * m_b[i] * k[i].xAcc;
            finalVel.yVel += deltaTime * m_b[i] * k[i].yAcc;
            finalVel.zVel += deltaTime * m_b[i] * k[i].zAcc;
        }

        // Return compute velocity contribute
        return finalVel;
    }
}