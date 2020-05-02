#pragma once
/*
    This files defines a base class for all drives
    and a driver manager class for easy managment of all drives
*/
namespace MoeP
{
    namespace hardware
    {
        class Driver
        {
        protected:

        public:
            Driver();
            ~Driver();
            virtual void Activate();
            virtual void Deactivate();
        };

        class DriverManager
        {
        private:
            Driver *drivers[256];
            int count;
        public:
            DriverManager();
            ~DriverManager();
            void AddDriver(Driver* driver);
            void ActivateAll();
            void DeactivateAll();
        };
    }
}