#ifndef   TV_APP_HPP_INCLUDED
#define   TV_APP_HPP_INCLUDED

#include <TVSource/Interfaces/IApp.hpp>

/// Provides the core game loop algorithm for all game engines.
class TimeVoyagerApp : public GQE::IApp
{
  public:
    /**
     * TicTacToeApp constructor
     * @param[in] theTitle is the title of the window
     */
    TimeVoyagerApp(const std::string theTitle = "TimeVoyager");

    /**
     * TicTacToeApp deconstructor
     */
    virtual ~TimeVoyagerApp();

  protected:
    /**
      * InitAssetHandlers is responsible for registering custom IAssetHandler
      * derived classes for a specific game application.
      */
    virtual void InitAssetHandlers(void);

    /**
      * InitScreenFactory is responsible for initializing any IScreen derived
      * classes with the ScreenManager class that will be used to create new
      * IScreen derived classes as requested.
      */
    virtual void InitScreenFactory(void);

    /**
      * HandleCleanup is responsible for performing any custom last minute
      * Application cleanup steps before exiting the Application.
      */
    virtual void HandleCleanup(void);

  private:
}; // class TicTacToeApp

#endif // TIC_TAC_TOE_APP_HPP_INCLUDED