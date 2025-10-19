#include "WebViewEditor.h"

namespace {
    const char* getMimeForExtension (const juce::String& extension)
    {
        using namespace juce;
        static const std::unordered_map<String, const char*> mimeMap =
        {
            { { "htm"   },  "text/html"                },
            { { "html"  },  "text/html"                },
            { { "txt"   },  "text/plain"               },
            { { "jpg"   },  "image/jpeg"               },
            { { "jpeg"  },  "image/jpeg"               },
            { { "svg"   },  "image/svg+xml"            },
            { { "ico"   },  "image/vnd.microsoft.icon" },
            { { "json"  },  "application/json"         },
            { { "png"   },  "image/png"                },
            { { "css"   },  "text/css"                 },
            { { "map"   },  "application/json"         },
            { { "js"    },  "text/javascript"          },
            { { "woff2" },  "font/woff2"               }
        };

        if (const auto it = mimeMap.find (extension.toLowerCase()); it != mimeMap.end())
            return it->second;

        jassertfalse;
        return "";
    }

    auto streamToVector (juce::InputStream& stream)
    {
        using namespace juce;
        std::vector<std::byte> result ((size_t) stream.getTotalLength());
        stream.setPosition (0);
        [[maybe_unused]] const auto bytesRead = stream.read (result.data(), result.size());
        jassert (bytesRead == (ssize_t) result.size());
        return result;
    }
}

PluginWebViewEditor::PluginWebViewEditor(PluginAudioProcessor& p)
    // initializer-list
    : AudioProcessorEditor(&p), processorRef(p),
    webView{
        juce::WebBrowserComponent::Options{}
        // Windows only: use WebView2 (Edge) instead of default (IE)
        .withBackend(juce::WebBrowserComponent::Options::Backend::webview2)
        // must specify user folder on Windows
        .withWinWebView2Options(juce::WebBrowserComponent::Options::WinWebView2{}
            .withUserDataFolder(juce::File::getSpecialLocation(juce::File::tempDirectory))
            .withBackgroundColour(juce::Colours::darkgrey))
        .withResourceProvider([this](const auto& url) {  // lambda
            return getResource(url);
        })
    }
{
    /*
    // Create WebBrowserComponent with WebView2 backend [from smart-pointer, instead of initializer-list]
    juce::WebBrowserComponent::Options options;
    options = options.withBackend(juce::WebBrowserComponent::Options::Backend::webview2)
        .withWinWebView2Options(juce::WebBrowserComponent::Options::WinWebView2{}
        .withUserDataFolder(juce::File::getSpecialLocation(juce::File::tempDirectory)));
    webView = std::make_unique<juce::WebBrowserComponent>(options);
    addAndMakeVisible(*webView);
    webView->goToURL("https://juce.com/learn/tutorials/");
    */

    juce::ignoreUnused(processorRef);

    addAndMakeVisible(webView);
    //webView.goToURL("https://juce.com/learn/tutorials/");
    // User-Interface in "res/ui/public/index.html"
    webView.goToURL(webView.getResourceProviderRoot());

    setResizable(true, true);
    setSize(800, 600);
}

PluginWebViewEditor::~PluginWebViewEditor()
{
}

void PluginWebViewEditor::resized()
{
    webView.setBounds(getLocalBounds());
    /*
    if (webView != nullptr)
        webView->setBounds(getLocalBounds());
    */
}

auto PluginWebViewEditor::getResource (const juce::String& url) -> std::optional<Resource> {
    static const auto resourceFileRoot = juce::File(R"(L:\WORKSPACES\AUDIO_WS\Projects\VJi\res\ui\public)");
    //static const auto resourceFileRoot = juce::File("res/ui/public/");
    const auto resourceToRetrieve = url == "/" ? "index.html" : url.fromFirstOccurrenceOf("/", false, false);
    const auto resource = resourceFileRoot.getChildFile(resourceToRetrieve).createInputStream();
    if (resource) {
        const auto extension = resourceToRetrieve.fromLastOccurrenceOf(".", false, false);
        // copy functions from lib/juce/examples/Plugins/WebViewPluginDemo.h (see head of this file)
        return Resource{streamToVector(*resource), getMimeForExtension(extension)};
    }
    return std::nullopt;
}
