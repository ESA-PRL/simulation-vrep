#include <boost/test/unit_test.hpp>
#include <vrep/Dummy.hpp>

using namespace vrep;

BOOST_AUTO_TEST_CASE(it_should_not_crash_when_welcome_is_called)
{
    vrep::DummyClass dummy;
    dummy.welcome();
}
