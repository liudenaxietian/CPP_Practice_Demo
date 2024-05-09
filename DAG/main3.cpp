#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class module
{
public:
  module(const string name, const vector<string> deps) :name_(name), deps_(deps){};
  virtual void execute() = 0;

  string Name()
  {
    return name_;
  }

  vector<string> &getDeps()
  {
    return deps_;
  }

private:
  string name_;
  vector<string> deps_;
};

class moduleA : public module
{
public:
  moduleA(const string name, const vector<string> deps) : module(name, deps){};
  void execute() override
  {
    cout << "moduleA executor: " << Name() << endl;
  }
};

class moduleB : public module
{
public:
  moduleB(const string name, const vector<string> deps) : module(name, deps){};
  void execute() override
  {
    cout << "moduleB executor: " << Name() << endl;
  }
};

class executor
{
public:
  void add_module(module *mod)
  {
    modules_[mod->Name()] = mod;
  }

  void executor_all()
  {
    unordered_map<string, bool> visited;
    for (auto &mod : modules_)
    {
      if (!visited[mod.first]) // 没有访问过
      {
        execute(mod.second, visited);
      }
    }
  }

private:
  void execute(module *mod, unordered_map<string, bool> &visited)
  {
    visited[mod->Name()] = true;
    for (auto dep : mod->getDeps())
    {
      if (!visited[dep])
      {
        execute(modules_[dep], visited);
      }
    }
    mod->execute();
  }
  unordered_map<string, module *> modules_;
};

int main(int argc, char *argv[])
{

  moduleA mA1 = {"A1", {}};
  moduleA mA2 = {"A2", {"A1"}};
  moduleB mB1 = {"B1", {"A1", "A2"}};
  moduleB mB2 = {"B2", {"A3"}};
  moduleA mA3 = {"A3", {"B1"}};

  executor e;
  e.add_module(&mB2);
  e.add_module(&mA2);
  e.add_module(&mA1);
  e.add_module(&mB1);
  e.add_module(&mA3);

  e.executor_all();

  return 0;
}