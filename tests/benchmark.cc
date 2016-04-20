/* Copyright 2003 - 2016, The libsigc++ Development Team
 *  Assigned to public domain.  Use as you wish without restriction.
 */

#include <iostream>
#include <sigc++/signal.h>
#include <sigc++/functors/mem_fun.h>
#include <glibmm/timeval.h>

const int COUNT = 10000000;

struct foo : public sigc::trackable
{
  int bar(int a);
  int c;
};

int foo::bar(int a)
{
  int b = c;
  c = a;
  return b;
}

void test_slot_call()
{
  foo foobar1;
  sigc::signal<int,int>::iterator it;

  // slot benchmark ...

  sigc::slot<int,int> slot = sigc::mem_fun(&foobar1, &foo::bar);

  std::cout << "elapsed time for calling a slot " << COUNT << " times:" << std::endl;.
  boost::timer::auto_cpu_timer timer;

  for (int i=0; i < COUNT; ++i)
    slot(i);
}

void test_signal_emit()
{
  sigc::signal<int,int> emitter;

  Glib::TimeVal t1, t2;
  t1.assign_current_time();

  for (int i=0; i < COUNT; ++i)
    emitter(i);

  t2.assign_current_time();
  t2.subtract(t1);

  std::cout << "elapsed time for " << COUNT << " emissions (0 slots): " << t2.tv_sec << "s " << t2.tv_usec << "us" << std::endl;
}

void test_connected_signal_emit()
{
  foo foobar1;
  sigc::signal<int,int> emitter;
  emitter.connect(mem_fun(&foobar1, &foo::bar));

  Glib::TimeVal t1, t2;
  t1.assign_current_time();

  for (int i=0; i < COUNT; ++i)
    emitter(i);

  t2.assign_current_time();
  t2.subtract(t1);

  std::cout << "elapsed time for " << COUNT << " emissions (1 slot): " << t2.tv_sec << "s " << t2.tv_usec << "us" << std::endl;
}

void test_connected_multiple_signal_emit()
{
  foo foobar1, foobar2, foobar3, foobar4, foobar5;

  sigc::signal<int,int> emitter;
  emitter.connect(mem_fun(&foobar2, &foo::bar));
  emitter.connect(mem_fun(&foobar3, &foo::bar));
  emitter.connect(mem_fun(&foobar4, &foo::bar));
  emitter.connect(mem_fun(&foobar5, &foo::bar));

  Glib::TimeVal t1, t2;
  t1.assign_current_time();

  for (int i=0; i < COUNT; ++i)
    emitter(i);

  t2.assign_current_time();
  t2.subtract(t1);

  std::cout << "elapsed time for " << COUNT << " emissions (5 slots): " << t2.tv_sec << "s " << t2.tv_usec << "us" << std::endl;
}

void test_connect_disconnect()
{
  foo foobar1;
  sigc::signal<int, int> emitter;
  sigc::signal<int, int>::iterator it;

  Glib::TimeVal t1, t2;
  t1.assign_current_time();

  for (int i=0; i < COUNT; ++i)
    {
      it = emitter.connect(mem_fun(&foobar1, &foo::bar));
      it->disconnect();
    }

  t2.assign_current_time();
  t2.subtract(t1);

  std::cout << "elapsed time for " << COUNT << " connections/disconnections: " << t2.tv_sec << "s " << t2.tv_usec << "us" << std::endl;
}

int main()
{
  // slot benchmark ...
  test_slot_call();

  // emission benchmark (zero slots) ...
  test_signal_emit();

  // emission benchmark (one slot) ...
  test_connected_signal_emit();

  // emission benchmark (five slot) ...
  test_connected_multiple_signal_emit();

  // connection / disconnection benchmark ...
  test_connect_disconnect();
}