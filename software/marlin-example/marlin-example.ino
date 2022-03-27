// Heater watch handling
template <int INCREASE, int HYSTERESIS, millis_t PERIOD>
struct HeaterWatch {
  celsius_t target;
  millis_t next_ms;
  inline bool elapsed(const millis_t &ms) { return next_ms && ELAPSED(ms, next_ms); }
  inline bool elapsed() { return elapsed(millis()); }

  inline bool check(const celsius_t curr) { return curr >= target; }

  inline void restart(const celsius_t curr, const celsius_t tgt) {
    if (tgt) {
      const celsius_t newtarget = curr + INCREASE;
      if (newtarget < tgt - HYSTERESIS - 1) {
        target = newtarget;
        next_ms = millis() + SEC_TO_MS(PERIOD);
        return;
      }
    }
    next_ms = 0;
  }
};
