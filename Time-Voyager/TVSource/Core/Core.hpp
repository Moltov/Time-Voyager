/**
 * Provides the GQE namespace includes for the GQE Core engine includes and
 * variables.
 *
 * @file include/GQE/Core.hpp
 * @author Ryan Lindeman
 * @date 20100710 - Initial Release
 * @date 20110118 - Added ConfigReader and StateManager includes.
 * @date 20110127 - Changed name from GQE.hpp to Core.hpp and moved to include
 * @date 20110218 - Added ConfigAsset to Core includes
 * @date 20110906 - Added new StringUtil include file
 * @date 20120512 - Add new Asset Handler classes
 * @date 20120702 - Add new EventManager and IEvent classes
 * @date 20120720 - Moved PropertyManager to Core library from Entity library beep
 */
#ifndef   GQE_CORE_HPP_INCLUDED
#define   GQE_CORE_HPP_INCLUDED

/////////////////////////////////////////////////////////////////////////////
// Headers
/////////////////////////////////////////////////////////////////////////////
#include <TVSource/Core/Config.hpp>
#include <TVSource/Core/Core_Types.hpp>

// GQE Core includes
#include <TVSource/Assets/ConfigAsset.hpp>
#include <TVSource/Assets/ConfigHandler.hpp>
#include <TVSource/Assets/FontAsset.hpp>
#include <TVSource/Assets/FontHandler.hpp>
#include <TVSource/Assets/ImageAsset.hpp>
#include <TVSource/Assets/ImageHandler.hpp>
#include <TVSource/Assets/MusicAsset.hpp>
#include <TVSource/Assets/MusicHandler.hpp>
#include <TVSource/Assets/SoundAsset.hpp>
#include <TVSource/Assets/SoundHandler.hpp>
#include <TVSource/Managers/AssetManager.hpp>
#include <TVSource/Managers/ConfigReader.hpp>
#include <TVSource/Managers/EventManager.hpp>
#include <TVSource/Managers/PropertyManager.hpp>
#include <TVSource/Managers/StateManager.hpp>
#include <TVSource/Managers/StatManager.hpp>
#include <TVSource/Interfaces/IApp.hpp>
#include <TVSource/Interfaces/IAssetHandler.hpp>
#include <TVSource/Interfaces/IEvent.hpp>
#include <TVSource/Interfaces/ILogger.hpp>
#include <TVSource/Interfaces/IProperty.hpp>
#include <TVSource/Interfaces/IState.hpp>
#include <TVSource/Interfaces/TAsset.hpp>
#include <TVSource/Interfaces/TAssetHandler.hpp>
#include <TVSource/Interfaces/TEvent.hpp>
#include <TVSource/Interfaces/TProperty.hpp>
#include <TVSource/Loggers/Log_macros.hpp>
#include <TVSource/Loggers/FatalLogger.hpp>
#include <TVSource/Loggers/FileLogger.hpp>
#include <TVSource/Loggers/ScopeLogger.hpp>
#include <TVSource/Loggers/StringLogger.hpp>
//#include <GQE/Core/loggers/onullstream>
//#include <GQE/Core/states/SplashState.hpp>
#include <TVSource/Utils/StringUtil.hpp>

#endif // GQE_CORE_HPP_INCLUDED

/**
 * @defgroup Core GQE Core module
 * The GQE Core module/library provides all basic classes used by all game
 * engines in the GQE collection of modules/libraries. Each game engine genre
 * will be built on top of the GQE Core module/library.
 *
 * Copyright (c) 2010-2011 Ryan Lindeman
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
