#pragma once
#ifndef MODULES_MANAGER_H_
#define MODULES_MANAGER_H_

namespace BiuLab {
namespace Modules {

class ModulesManager {
   private:
   public:
    void LoadModule();

    void UnloadModule();

    ModulesManager();

    ~ModulesManager();
};

}  // namespace Modules

}  // namespace BiuLab

#endif