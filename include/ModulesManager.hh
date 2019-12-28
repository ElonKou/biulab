#pragma once
#ifndef MODULES_MANAGER_H_
#define MODULES_MANAGER_H_

class ModulesManager {
   private:
   public:
    void LoadModule();

    void UnloadModule();

    ModulesManager();

    ~ModulesManager();
};

#endif