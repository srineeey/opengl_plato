//
// Created by sriney on 4/15/21.
//

namespace test{

    class Test
    {
    public:
        Test();
        virtual ~Test() {};

                virtual void OnUpdate(float deltaTime) {};
                virtual void OnRender() {};
                virtual void OnImGuiRender() {};
    };



}
