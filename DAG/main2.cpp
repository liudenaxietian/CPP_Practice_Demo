#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class module
{
public:
  module(string name, vector<string> deps) :name_(name), deps_(deps){};
  virtual void executor() = 0;
  const string &Name() const { return name_; }
  const vector<string> &Deps() const { return deps_; }

private:
  string name_;
  vector<string> deps_;
};

class moduleA : public module
{
public:
  moduleA(string name, vector<string> deps) : module(name, deps){};
  void executor() override
  {
    cout << "moduleA executor" << Name() << endl;
  }
};

class moduleB : public module
{
public:
  moduleB(string name, vector<string> deps) : module(name, deps){};
  void executor() override
  {
    cout << "moduleB executor" << Name() << endl;
  }
};

class execute
{
public:
  void add_module(module *mod)
  {
    modules_[mod->Name()] = mod;
  }
  void execute_all()
  {
    unordered_map<string, bool> visited;
    for (auto mod : modules_)
    {
      if (!visited[mod.first])
      {
        executor(mod.second, visited);
      }
    }
  }

private:
  void executor(module* mod,unordered_map<string,bool>& visited)
  {
    visited[mod->Name()] = true;
    for(auto dep:mod->Deps()){
      if(!visited[dep]){
        executor(modules_[dep],visited);
      }
    }
    mod->executor();
  }
  unordered_map<string, module *> modules_;
};


int main(){
  moduleA mA1("A1",{});
  moduleA mA2("A2",{"A1"});
  moduleB mB1("B1",{"A1","A2"});
  moduleA mA3("A3",{"B1"});

  execute e;
  e.add_module(&mA3);
  e.add_module(&mB1);
  e.add_module(&mA1);
  e.add_module(&mA2);


  e.execute_all();

  return 0;
}