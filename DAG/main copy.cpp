#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

class module
{
public:
  module(string name, vector<string> deps) :name_(name), deps_(deps){};
  virtual void executor() = 0;
  const string &name() const { return name_; }
  const vector<string> &deps() const { return deps_; }

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
    cout << "moduleA executor" << name() << endl;
  }
};

class moduleB : public module
{
public:
  moduleB(string name, vector<string> deps) : module(name, deps){};
  void executor() override
  {
    cout << "moduleB executor" << name() << endl;
  }
};

class executor
{
public:
  void add_module(module *mod)
  {
    modules_[mod->name()] = mod;
  }

  void execute_all()
  {
    unordered_map<string, bool> visited;
    for (auto &mod_pair : modules_)
    {
      if (!visited[mod_pair.first])
      {
        execute(mod_pair.second, visited);
      }
    }
  }

private:
  void execute(module *mod, unordered_map<string, bool> &visited)
  {
    visited[mod->name()] = true;
    for (auto &dep : mod->deps())
    {
      if (!visited[dep])
      {
        execute(modules_[dep], visited);
      }
    }
    mod->executor();
  }
  unordered_map<string, module *> modules_;
};

int main()
{
  moduleA mA1("A1", {});
  moduleA mA3("A3", {"B1"});
  moduleB mB1("B1", {"A1", "A2"});
  moduleA mA2("A2", {"A1"});

  executor e;
  e.add_module(&mA1);
  e.add_module(&mA2);
  e.add_module(&mA3);
  e.add_module(&mB1);

  e.execute_all();

  return 0;
}