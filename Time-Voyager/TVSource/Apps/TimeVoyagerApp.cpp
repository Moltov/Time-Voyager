/**
 * Provides the TicTacToeApp class which implements the TicTacToe example game
 * for the GQE library.
 *
 * @file examples/demo/TicTacToeApp.cpp
 * @author Ryan Lindeman
 * @date 20110704 - Initial Release
 * @date 20120512 - Add new Init methods required by IApp base class
 */
#include <TVSource/Apps/TimeVoyagerApp.hpp>
#include <TVSource/Apps/GameState.hpp>

TimeVoyagerApp::TimeVoyagerApp(const std::string theTitle) :
GQE::IApp(theTitle)
{
}

TimeVoyagerApp::~TimeVoyagerApp()
{
}

void TimeVoyagerApp::InitAssetHandlers(void)
{
  // No custom asset handlers needed or provided
}

void TimeVoyagerApp::InitScreenFactory(void)
{
  // Add Game State as the next active state
  mStateManager.AddActiveState(new(std::nothrow) GameState(*this));
}

void TimeVoyagerApp::HandleCleanup(void)
{
  // No custom cleanup needed
}