#include "TreeNode/TreeNode.hpp"
#include <iostream>
#include <sstream>
#include <cassert>
#include <cmath>
#include <vector>

namespace NBodyEnv
{
    // static variables initialization
    double TreeNode::m_theta = 0.9;
    double TreeNode::m_G = 6.67408e-11;

    TreeNode::TreeNode(const std::vector<double> &max, const std::vector<double> &min, TreeNode *parent)
        : m_totMass(0.0),
          m_cm({0.0, 0.0, 0.0}),
          m_center({min[0] + (max[0] - min[0]) / 2.0, min[1] + (max[1] - min[1]) / 2.0, min[2] + (max[2] - min[2]) / 2.0}),
          m_max(max),
          m_min(min),
          m_parent(parent),
          m_nParticles(0),
          m_tooClose(false),
          // initialize with dummy particle
          m_particle(NBodyEnv::gravitational, {0.0, 0.0, 0.0},
                     {0.0, 0.0, 0.0}, 0.0, 0)
    {
        for (int i = 0; i < 8; i++)
        {
            // all children initially don't exist
            m_octant[i] = nullptr;
        }
    }

    // getters
    double TreeNode::GetMass() const
    {
        return m_totMass;
    }

    const std::vector<double> &TreeNode::GetCenterOfMass() const
    {
        return m_cm;
    }

    const std::vector<double> &TreeNode::GetCenter() const
    {
        return m_center;
    }

    TreeNode *TreeNode::GetParent() const
    {
        return m_parent;
    }

    int TreeNode::GetNParticles() const
    {
        return m_nParticles;
    }

    double TreeNode::GetTheta() const
    {
        return m_theta;
    }

    std::vector<double> TreeNode::GetMax() const
    {
        return m_max;
    }

    std::vector<double> TreeNode::GetMin() const
    {
        return m_min;
    }

    // setters
    void TreeNode::SetMass(double mass)
    {
        m_totMass = mass;
    }

    void TreeNode::SetCenterOfMass(const std::vector<double> &cm)
    {
        m_cm = cm;
    }

    void TreeNode::SetCenter(const std::vector<double> &center)
    {
        m_center = center;
    }

    void TreeNode::SetParent(TreeNode *parent)
    {
        m_parent = parent;
    }

    void TreeNode::SetNParticles(int nParticles)
    {
        m_nParticles = nParticles;
    }

    void TreeNode::SetTheta(double theta)
    {
        m_theta = theta;
    }

    bool TreeNode::IsRoot() const
    {
        return m_parent == nullptr;
    }

    bool TreeNode::IsExternal() const
    {
        return m_octant[0] == nullptr && m_octant[1] == nullptr && m_octant[2] == nullptr && m_octant[3] == nullptr && m_octant[4] == nullptr && m_octant[5] == nullptr && m_octant[6] == nullptr && m_octant[7] == nullptr;
    }

    void TreeNode::ResetNode(const std::vector<double> &max, const std::vector<double> &min)
    {
        if (!IsRoot()) // only the root can be reset
        {
            std::cout << "Error: can't reset a node that is not the root\n";
            return;
        }

        m_totMass = 0.0;
        m_cm = {0.0, 0.0, 0.0};
        m_max = max;
        m_min = min;
        m_center = {min[0] + (max[0] - min[0]) / 2.0, min[1] + (max[1] - min[1]) / 2.0, min[2] + (max[2] - min[2]) / 2.0};
        m_parent = nullptr;
        m_nParticles = 0;
        m_cm = {0.0, 0.0, 0.0};
        m_tooClose = false;
        m_particle = Particle(NBodyEnv::gravitational, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 0.0, 0);
        for (int i = 0; i < 8; i++)
        {
            // all children initially don't exist
            delete m_octant[i];
            m_octant[i] = nullptr;
        }
    }

    // method to get an octant of the current node based on the position of a particle inside that node
    TreeNode::Octant TreeNode::GetOctant(double x, double y, double z) const
    {
        if (x > m_center[0])
        {
            if (y > m_center[1])
            {
                if (z > m_center[2])
                {
                    return NEE;
                }
                else
                {
                    return SEE;
                }
            }
            else
            {
                if (z > m_center[2])
                {
                    return NWE;
                }
                else
                {
                    return SWE;
                }
            }
        }
        else
        {
            if (y > m_center[1])
            {
                if (z > m_center[2])
                {
                    return NEI;
                }
                else
                {
                    return SEI;
                }
            }
            else
            {
                if (z > m_center[2])
                {
                    return NWI;
                }
                else
                {
                    return SWI;
                }
            }
        }
    }

    void TreeNode::PrintOctant(Octant octant) const
    {
        switch (octant)
        {
        case SWI:
            std::cout << "SWI\n";
            break;
        case SWE:
            std::cout << "SWE\n";
            break;
        case SEE:
            std::cout << "SEE\n";
            break;
        case SEI:
            std::cout << "SEI\n";
            break;
        case NWI:
            std::cout << "NWI\n";
            break;
        case NWE:
            std::cout << "NWE\n";
            break;
        case NEE:
            std::cout << "NEE\n";
            break;
        case NEI:
            std::cout << "NEI\n";
            break;

        default:
            std::cout << "Error: Octant not found\n";
        }
    }

    // method to create a new node, which amounts tot creating a new Node of the Octree
    // this is done upon insertion of a particle in a node that already contains a particle
    // so that the node is subdivided and the two particles are relocated in the correct octants
    TreeNode *TreeNode::CreateNode(Octant octant)
    {
        switch (octant)
        {
        case SWI:
            return new TreeNode(m_center, m_min, this);
            break;
        case SWE:
            return new TreeNode({m_max[0], m_center[1], m_center[2]}, {m_center[0], m_min[1], m_min[2]}, this);
            break;
        case SEE:
            return new TreeNode({m_max[0], m_max[1], m_center[2]}, {m_center[0], m_center[1], m_min[2]}, this);
            break;
        case SEI:
            return new TreeNode({m_center[0], m_max[1], m_center[2]}, {m_min[0], m_center[1], m_min[2]}, this);
            break;
        case NWI:
            return new TreeNode({m_center[0], m_center[1], m_max[2]}, {m_min[0], m_min[1], m_center[2]}, this);
            break;
        case NWE:
            return new TreeNode({m_max[0], m_center[1], m_max[2]}, {m_center[0], m_min[1], m_center[2]}, this);
            break;
        case NEE:
            return new TreeNode(m_max, m_center, this);
            break;
        case NEI:
            return new TreeNode({m_center[0], m_max[1], m_max[2]}, {m_min[0], m_center[1], m_center[2]}, this);
            break;

        default:
            std::stringstream ss;
            ss << "Can't determine quadrant!\n";
            throw std::runtime_error(ss.str().c_str());
            break;
        }
    }

    void TreeNode::InsertParticle(const Particle &part, int level)
    {
        if ((part.getPos().xPos < m_min[0] || part.getPos().xPos > m_max[0]) || (part.getPos().yPos < m_min[1] || part.getPos().yPos > m_max[1]) || (part.getPos().zPos < m_min[2] || part.getPos().zPos > m_max[2]))
        {
            std::stringstream ss;
            // print particle position
            ss << "Particle position: (" << part.getPos().xPos << ", " << part.getPos().yPos << ", " << part.getPos().zPos << ")";
            ss << " is out of boundaries!\n";
            // print min and max
            ss << "Min: (" << m_min[0] << ", " << m_min[1] << ", " << m_min[2] << ")";
            ss << "Max: (" << m_max[0] << ", " << m_max[1] << ", " << m_max[2] << ")";
            throw std::runtime_error(ss.str());
        }

        // the node is an inner node, need to sink the particle further down
        if (m_nParticles > 1)
        {
            Octant octant = GetOctant(part.getPos().xPos, part.getPos().yPos, part.getPos().zPos);
            // PrintOctant(octant);
            if (!m_octant[octant])
            {
                m_octant[octant] = CreateNode(octant);
            }

            m_octant[octant]->InsertParticle(part, level + 1);
        }

        // the node is an external node, but is already occupied by a particle
        // need to relocate both particles in the correct octants
        else if (m_nParticles == 1)
        {
            assert(IsExternal() || IsRoot());

            // first the particle that was already in the node
            Octant octant = GetOctant(m_particle.getPos().xPos, m_particle.getPos().yPos, m_particle.getPos().zPos);
            // PrintOctant(octant);
            if (m_octant[octant] == nullptr)
            {
                m_octant[octant] = CreateNode(octant);
            }
            m_octant[octant]->InsertParticle(m_particle, level + 1);

            // then the new particle
            octant = GetOctant(part.getPos().xPos, part.getPos().yPos, part.getPos().zPos);
            // PrintOctant(octant);
            if (m_octant[octant] == nullptr)
            {
                m_octant[octant] = CreateNode(octant);
            }
            m_octant[octant]->InsertParticle(part, level + 1);
        }

        // node is an external node and is empty ==> insert particle and terminate recursion
        else if (m_nParticles == 0)
        {
            // assign particle as the new particle in the node
            m_particle = part;
        }

        m_nParticles++;
    }

    void TreeNode::ComputeMass()
    {
        // node is an external node, terminate recursion
        if (m_nParticles == 1)
        {
            assert(m_particle.getSpecInfo());
            m_totMass = m_particle.getSpecInfo();
            m_cm = std::vector<double>{m_particle.getPos().xPos, m_particle.getPos().yPos, m_particle.getPos().zPos};
        }

        // node is an internal node, compute mass of all children
        else
        {
            m_totMass = 0.0;
            m_cm = std::vector<double>{0.0, 0.0, 0.0};

            for (int i = 0; i < 8; ++i)
            {
                // consider only the octants that actually exist, i.e. are not nullptr and
                // point to a TreeNode object
                if (m_octant[i])
                {
                    m_octant[i]->ComputeMass();
                    m_totMass += m_octant[i]->m_totMass;
                    m_cm[0] += m_octant[i]->m_cm[0] * m_octant[i]->m_totMass;
                    m_cm[1] += m_octant[i]->m_cm[1] * m_octant[i]->m_totMass;
                    m_cm[2] += m_octant[i]->m_cm[2] * m_octant[i]->m_totMass;
                }
            }

            m_cm[0] /= m_totMass;
            m_cm[1] /= m_totMass;
            m_cm[2] /= m_totMass;
        }
    }

    void TreeNode::PrintNodesWithParticles(const TreeNode *node)
    {
        if (node->IsExternal() && node->GetNParticles() > 0)
        {
            // Print information about the node containing particles
            std::cout << "Node Center: " << node->GetCenter()[0] << " " << node->GetCenter()[1] << " " << node->GetCenter()[2] << std::endl;
            std::cout << "Node Octant: ";
            node->PrintOctant(node->GetOctant(node->m_particle.getPos().xPos, node->m_particle.getPos().yPos, node->m_particle.getPos().zPos));
            std::cout << "Particle Info: "
                      << "Mass=" << node->m_particle.getSpecInfo() << ", Position=("
                      << node->m_particle.getPos().xPos << ", " << node->m_particle.getPos().yPos << ", " << node->m_particle.getPos().zPos << ")" << std::endl;
            std::cout << "------------------------" << std::endl;
        }
        else
        {
            for (int i = 0; i < 8; ++i)
            {
                if (node->m_octant[i])
                {
                    PrintNodesWithParticles(node->m_octant[i]);
                }
            }
        }
    }

    std::vector<double> TreeNode::ComputeForce(const Particle &p1) const
    {
        // calculate the force from the barnes hut tree to the particle p1
        std::vector<double> acc = {0.0, 0.0, 0.0};
        double r(0), k(0), d(0);

        // MAC coefficient was too stringent, treat this contribution as direct sum algorithm would do
        // ==> compute the force between two single particles
        if (m_nParticles == 1)
        {
            acc = ComputeAcc(p1, m_particle);
        }
        else
        {
            // obtain distance between current particle and node center of mass
            r = sqrt((p1.getPos().xPos - m_cm[0]) * (p1.getPos().xPos - m_cm[0]) +
                     (p1.getPos().yPos - m_cm[1]) * (p1.getPos().yPos - m_cm[1]) +
                     (p1.getPos().zPos - m_cm[2]) * (p1.getPos().zPos - m_cm[2]));
            // obtain node width
            d = m_max[0] - m_min[0];

            // check if the node is too close to the particle w.r.t. its size
            if ((d / r) <= m_theta)
            {
                // approximate force contribution of all particles in this node
                // as a single particle located in the center of mass of the node
                m_tooClose = false;
                k = m_G * m_totMass / (r * r * r);
                acc[0] = k * (m_cm[0] - p1.getPos().xPos);
                acc[1] = k * (m_cm[1] - p1.getPos().yPos);
                acc[2] = k * (m_cm[2] - p1.getPos().zPos);
            }
            else // need to consider the non null children, approximation was too coarse
            {
                m_tooClose = true;
                std::vector<double> buf = {0.0, 0.0, 0.0};
                for (int q = 0; q < 8; ++q)
                {
                    if (m_octant[q])
                    {
                        buf = m_octant[q]->ComputeForce(p1);
                        acc[0] += buf[0];
                        acc[1] += buf[1];
                        acc[2] += buf[2];
                    }
                }
            }
        }
        return acc;
    }

    std::vector<double> TreeNode::ComputeAcc(const Particle &p1, const Particle &p2) const
    {
        std::vector<double> acc = {0.0, 0.0, 0.0};
        // check if the two particles are in the same position, hence are the same particle
        // ==> return zero acceleration
        // this is necessary to avoid singularities in the force computation,
        // though it should be virtually impossible for two different particles to be in the same position
        if (p1.getPos().xPos == p2.getPos().xPos && p1.getPos().yPos == p2.getPos().yPos && p1.getPos().zPos == p2.getPos().zPos)
        {
            return acc;
        }

        const double &x1(p1.getPos().xPos),
            &y1(p1.getPos().yPos), &z1(p1.getPos().zPos);
        const double &x2(p2.getPos().xPos),
            &y2(p2.getPos().yPos), &z2(p2.getPos().zPos),
            &m2(p2.getSpecInfo());

        double r = sqrt((x1 - x2) * (x1 - x2) +
                        (y1 - y2) * (y1 - y2) +
                        (z1 - z2) * (z1 - z2));

        double k = m_G * m2 / (r * r * r);

        acc[0] += k * (x2 - x1);
        acc[1] += k * (y2 - y1);
        acc[2] += k * (z2 - z1);

        return acc;
    }

    TreeNode::~TreeNode()
    {
        for (int i = 0; i < 8; ++i)
        {
            if (m_octant[i])
            {
                delete m_octant[i];
            }
        }
    }

}
