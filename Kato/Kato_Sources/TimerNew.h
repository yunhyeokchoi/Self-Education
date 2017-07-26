#include <chrono>

namespace KatoEngine
{
  using namespace std::chrono;

  namespace
  {
    time_point<high_resolution_clock> prevTime;
    time_point<high_resolution_clock> currTime;
  }

  class TimerNew
  {
    public:
      static void Initialize(void)
      {
        prevTime = currTime = high_resolution_clock::now();
      }

      static float GetDelta(void)
      {
        currTime = high_resolution_clock::now();

        //We get the time difference in float.
        duration<float> delta(currTime - prevTime);

        prevTime = high_resolution_clock::now();
        //or we can do...
        //prevTime = currTime;

        return delta.count();
      }
    private:
  };
}