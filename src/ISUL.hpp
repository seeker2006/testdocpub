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
        @brief Unique identifier for product, human readable, for example @cite PRISM
     */
    extern const std::string kProductID;

    /*!
        @brief Product version string
     */
    extern const std::string kProductVersion;

    /*!
        @brief Location (file system path) where to store received activation tokens
     */
    extern const std::string kLicenceStoragePath;

    /*!
        @brief Location (logging file path)
     */
    extern const std::string kLogFilePath;

    /*!
        @brief Number of offline application launches (PhoneHome grace period parameter)
     */
    extern const std::string kOfflineAppLaunches;

    /*!
        @brief Time of last successfull connection to license server (PhoneHome grace period parameter)
     */
    extern const std::string kLastPassConnect;

    /*!
        @brief Time of starting last day expiration (PhoneHome grace period parameter)
     */
    extern const std::string kLastDayExpiration;

    /*!
        @brief Names of Phone Home events
     */
    extern const std::string kPHO_AppLaunch;
    extern const std::string kPhoneHomeEventNameAppExit;
    extern const std::string kPHO_Activation;
    extern const std::string kPHO_AutoLaunch;
    extern const std::string kPHO_About;
    extern const std::string kPHO_Background;
    extern const std::string kPHO_Renew;

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
            @brief Control wether ISUL should show WebUI in the case phone home failed
            @param status Status of previous condition, which leads to this call
            @return true if client whould like to allwo WebUI or false if not
         */
        virtual bool ShouldStartActivation(Status::ptr status) { return true; }

        /*!
            @brief Called after the validation has finised.
            @param status Contains status of validation operation
         */
        virtual void OnValidationFinished(Status::ptr status) {}
        
        virtual void OnServerLog(ServerStatus status, LogSeverity severity, const std::string& message, const std::string& content) {}

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
        
        static Manager::ptr Create(const std::string& uiURL, const std::string& offlineUIURL, const std::string& apiURL, const Properties& productInfo, Delegate::weak_ptr delegate);

        /*!
            @brief  Validate current activation state for specifed product
            Shows sign-in dialog in the case activation state is invalid
            or phone home with existing activaion, thus renewing state
            @param reason platform specific UI context, where WebUI will be rendered
         */
        void Validate(const std::string& reason);

        /*!
            @brief Return user friendly information from actyivation tokens as dictionary
            @param info returned license info
         */
        void CopyLicenseInfo(Properties& info);
        
        
        

        /*!
            @brief Forces to renew a license file with current product info
            (offline PhoneHome parameters)
        */
        void UpdateLicenseInfo();

        /*!
            @brief Deactivate current activation
            @param callback lient provided endpoint, called as a result of Server request completion
            use @p callback when it needed only
         */
        void Deactivate(std::function<void(Status::ptr status)> callback);

    private:
        
        /// @cond Private memebers
        Manager(const std::string& uiURL, const std::string& apiURL, const Properties& productInfo, Delegate::weak_ptr delegate);
        Manager(const std::string& uiURL, const std::string& offlineUIURL, const std::string& apiURL, const Properties& productInfo, Delegate::weak_ptr delegate);
        class Impl;
        std::shared_ptr<Impl> impl;
        /// @endcond
    };
}
