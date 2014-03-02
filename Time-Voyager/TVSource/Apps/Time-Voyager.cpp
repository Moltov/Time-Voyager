// Time-Voyager.cpp : Defines the entry point for the console application.
//

#include <TVSource/Core/stdafx.h>
#include <TVSource/Apps/TimeVoyagerApp.hpp>
#include <TVSource/Core/Core.hpp>
#include <assert.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main(int argc, char* argv[])
{
  // Default anExitCode to a specific value
  int anExitCode = GQE::StatusNoError;

  // Create a FileLogger and make it the default logger before creating our App
  GQE::FileLogger anLogger("output.txt", true);

  // Create our action application.
  GQE::IApp* anApp = new(std::nothrow) TimeVoyagerApp();
  assert(NULL != anApp && "main() Can't create Application");

  // Process command line arguments
  anApp->ProcessArguments(argc, argv);

  // Start the action application:
  // Initialize the action application
  // Enter the Game Loop where the application will remain until it is shutdown
  // Cleanup the action application
  // Exit back to here
  anExitCode = anApp->Run();

  // Cleanup ourselves by deleting the action application
  delete anApp;

  // Don't keep pointers to objects we have just deleted
  anApp = NULL;

  // return our exit code
  return anExitCode;
}
