#pragma once

/*

OpenArabTools version 0.1
ONLY INCLUDE THIS FILE - ALL OTHERS WILL BE INCLUDED AUTOMATICALLY

*/

#include "../src/Utils.hpp"
#include "../src/event/Event.hpp"
#include "../src/graphics/Graphics.hpp"
#include "../src/remote/Remote.hpp"
#include "../src/types/LightColor.hpp"

#ifndef OPENARABTOOLS_NO_NAMESPACE_OVERRIDE
namespace ArabTools = OpenArabTools;
namespace oAT = OpenArabTools;
namespace AT = ArabTools;
#endif

/*
OPENARABTOOLS configuration macros
DEFINE THESE MACROS BEFORE INCLUDING
--

OPENARABTOOLS_NO_EXTENSIONS
Disables extensions specific for openArabTools

OPENARABTOOLS_NO_SOLUTIONS
Disables solutions (classes with implement a particular finished thing e.g. Cube, Semaphore)

OPENARABTOOLS_NO_STANDARD_INCLUDE
Disables openArabTools specific includes

OPENARABTOOLS_NO_NAMESPACE_OVERRIDE
Disables ArabTools, oAT and AT namespaces

--
*/