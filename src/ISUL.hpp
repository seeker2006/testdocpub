/*!
    @file ISUL.hpp
    ISUL
 
    @author
    @date 05.04.2021
    @brief ISUL C++  interface
*/

#pragma once

/*!
    @mainpage
    @section intro_sec Overview
    The library is a platform-native C++ layer adopting the ISUL system for desktop apps. It implements all interactions with ISUL service providing a minimally required interface to the client apps for invoking the functionality and controlling the behavior.
    @section install_sec Installation
    @subsection step1 Step 1: ...
  
 
   etc...
 */

/// @cond STL includes
#include <functional>
#include <map>
/// @endcond
#include "Status.hpp"

/*!
    @brief Common namespace for ISUL C++ interfaces
 */
namespace ISUL {

    /*!
        @brief Type for dictionary of values
     */
    typedef std::map<std::string, std::string> Properties;

    /*!
        @brief Delegate interface should be implemented by client to receive status or control ISUL workflow
     */
    class Delegate {
    public:
        using ptr = std::shared_ptr<Delegate>;
        using weak_ptr = std::weak_ptr<Delegate>;

        /*!
            @brief Get the Content View object
            @return Platform specific container. HWND for Windows and NSView* for Mac
         */
        virtual void* GetContentView() = 0;
        
        /*!
            @brief Called if client select old axtivation method, implemented independently in the client application
         */
        virtual void OnFallback() {}
    };

    /*!
        @brief Main interface to operate with ISUL licenses
     */
    class Manager {
    public:
        using ptr = std::shared_ptr<Manager>;
        virtual ~Manager();

        /*!
            @brief Create new instance of license manager
            @param uiURL URL for WebUI communication
            @param apiURL URL for ISUL API communication
            @param productInfo Set of configuration properties describing product
            @param delegate Delegate interface provided by client to get feedback
            @return new instance of license Manager
         */
        static Manager::ptr Create(const std::string& uiURL, const std::string& apiURL, const Properties& productInfo, Delegate::weak_ptr delegate);
        
        /*!
            @brief  Validate current activation state for specifed product
            Shows sign-in dialog in the case activation state is invalid
            or phone home with existing activaion, thus renewing state
            @param reason platform specific UI context, where WebUI will be rendered
         */
        void Validate(const std::string& reason);
        
        /*!
            @brief Deactivate current activation
            @param callback lient provided endpoint, called as a result of Server request completion
            use @p callback when it needed only
         */
        void Deactivate(std::function<void(Status::ptr status)> callback);

    private:
        
        /// @cond Private memebers
        Manager(const std::string& uiURL, const std::string& apiURL, const Properties& productInfo, Delegate::weak_ptr delegate);
        class Impl;
        std::shared_ptr<Impl> impl;
        /// @endcond
    };
}
