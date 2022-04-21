#ifndef BEACON_BROWSER_UI_WEBUI_BEACON_HNS_INTERNALS_BEACON_HNS_INTERNALS_UI_H_
#define BEACON_BROWSER_UI_WEBUI_BEACON_HNS_INTERNALS_BEACON_HNS_INTERNALS_UI_H_

#include "base/memory/raw_ptr.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "mojo/public/cpp/bindings/pending_remote.h"
#include "mojo/public/cpp/bindings/receiver.h"
#include "ui/base/resource/resource_scale_factor.h"
#include "ui/webui/mojo_web_ui_controller.h"
#include "ui/webui/resources/js/browser_command/browser_command.mojom.h"

namespace base {
class RefCountedMemory;
}

namespace content {
class WebUI;
}

class BrowserCommandHandler;
class PrefRegistrySimple;
class Profile;

// The Web UI controller for the chrome://hns-internals.
class BeaconHNSInternalsUI : public ui::MojoWebUIController,
                   public browser_command::mojom::CommandHandlerFactory {
 public:
  explicit BeaconHNSInternalsUI(content::WebUI* web_ui);
  ~BeaconHNSInternalsUI() override;

  static void RegisterLocalStatePrefs(PrefRegistrySimple* registry);

  static base::RefCountedMemory* GetFaviconResourceBytes(
      ui::ResourceScaleFactor scale_factor);

  // Instantiates the implementor of the
  // browser_command::mojom::CommandHandlerFactory mojo interface.
  void BindInterface(
      mojo::PendingReceiver<browser_command::mojom::CommandHandlerFactory>
          pending_receiver);

  BeaconHNSInternalsUI(const BeaconHNSInternalsUI&) = delete;
  BeaconHNSInternalsUI& operator=(const BeaconHNSInternalsUI&) = delete;

 private:
  // browser_command::mojom::CommandHandlerFactory
  void CreateBrowserCommandHandler(
      mojo::PendingReceiver<browser_command::mojom::CommandHandler>
          pending_handler) override;

  std::unique_ptr<BrowserCommandHandler> command_handler_;
  mojo::Receiver<browser_command::mojom::CommandHandlerFactory>
      browser_command_factory_receiver_;
  raw_ptr<Profile> profile_;
  WEB_UI_CONTROLLER_TYPE_DECL();
};

#endif  // BEACON_BROWSER_UI_WEBUI_BEACON_HNS_INTERNALS_BEACON_HNS_INTERNALS_UI_H_
