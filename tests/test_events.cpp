#include <catch2/catch_all.hpp>
#include <entt/entt.hpp>
#include "../src/core/events/events.hpp"

TEST_CASE("QuitEvent triggers handler")
{
    entt::dispatcher dispatcher;
    bool called = false;
    // Local handler to test
    auto handler = [&called](const core::QuitEvent<> &)
    { called = true; };
    dispatcher.sink<core::QuitEvent<>>().connect<&decltype(handler)::operator()>(&handler);
    dispatcher.trigger<core::QuitEvent<>>();
    REQUIRE(called);
}

TEST_CASE("Multiple handlers for same event")
{
    entt::dispatcher dispatcher;
    int call_count = 0;
    auto handler1 = [&call_count](const core::QuitEvent<> &)
    { call_count++; };
    auto handler2 = [&call_count](const core::QuitEvent<> &)
    { call_count++; };
    dispatcher.sink<core::QuitEvent<>>().connect<&decltype(handler1)::operator()>(&handler1);
    dispatcher.sink<core::QuitEvent<>>().connect<&decltype(handler2)::operator()>(&handler2);
    dispatcher.trigger<core::QuitEvent<>>();
    REQUIRE(call_count == 2);
}

TEST_CASE("Handler disconnect works")
{
    entt::dispatcher dispatcher;
    bool called = false;
    auto handler = [&called](const core::QuitEvent<> &)
    { called = true; };
    auto conn = dispatcher.sink<core::QuitEvent<>>().connect<&decltype(handler)::operator()>(&handler);
    dispatcher.sink<core::QuitEvent<>>().disconnect<&decltype(handler)::operator()>(&handler);
    dispatcher.trigger<core::QuitEvent<>>();
    REQUIRE_FALSE(called);
}

struct CustomEvent
{
    int value;
};

TEST_CASE("Custom event with data triggers handler")
{
    entt::dispatcher dispatcher;
    int received = 0;
    auto handler = [&received](const CustomEvent &e)
    { received = e.value; };
    dispatcher.sink<CustomEvent>().connect<&decltype(handler)::operator()>(&handler);
    dispatcher.trigger<CustomEvent>(CustomEvent{42});
    REQUIRE(received == 42);
}
