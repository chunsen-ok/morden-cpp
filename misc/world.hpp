#ifndef MCPP_WORLD_HPP
#define MCPP_WORLD_HPP

#include <vector>

namespace mcpp {

    class Object {
    public:
        Object(const std::string &name = std::string("")): m_name(name) {}
        virtual ~Object() {}

        void set_object_name(const std::string &name) {
            m_name = name;
        }

        const std::string &object_name() const {
            return m_name;
        }

    protected:
        std::string m_name;
    };

    class World {
    public:
        ~World() {
            for (Object *obj: m_objects) {
                if (obj) {
                    std::cout << "Destroy: " << obj->object_name() << std::endl;
                    delete obj;
                }
            }
            m_objects.clear();
        }

        void add_object(Object *obj) {
            if (obj) {
                m_objects.push_back(obj);
            }
        }

        int exec() {
            return 0;
        }

    protected:
        std::vector<Object*> m_objects;
    };
}

#endif
