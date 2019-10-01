/// \file snaphot.h Capture state for testing

#ifndef MOCK_TRAP_H
#define MOCK_TRAP_H

/// Store a captured value
///
/// \param C context where capture is stored
template<typename C>
class Snapshot {
  private:
    unsigned numCalls;
    // FIXME capture values seen in calls
    // FIXME How many instances are in this context
  protected:
    // TODO reset
    void capture() { ++numCalls; }
  public:
    unsigned getNumCalls() { return numCalls; }
    Snapshot() : numCalls(0) {}
};

/// Write value
template<typename C>
class SnapshotWriter : public Snapshot<C> {
  public:
    void set() { this->capture(); }
};

#endif // MOCK_TRAP_H
