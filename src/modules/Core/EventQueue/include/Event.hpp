#pragma once

#include <functional>

// EventHandler type definition
typedef std::function<bool(void*)> EventHandler;

// Event type definition
typedef int Event;
