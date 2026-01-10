#include <webview.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <curl/curl.h>

// FormatUI dev link
const std::string FORMATUI_LINK = "https://7640d732-016d-4f41-b2e1-a9b23de6fee2-00-2yg6qnr2lrtoi.janeway.replit.dev/";

// Background ping function
void keep_alive_ping() {
    while (true) {
        CURL *curl;
        CURLcode res;
        curl = curl_easy_init();
        if(curl) {
            curl_easy_setopt(curl, CURLOPT_URL, FORMATUI_LINK.c_str());
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);
            curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
            res = curl_easy_perform(curl);
            if(res != CURLE_OK)
                std::cerr << "Ping failed: " << curl_easy_strerror(res) << "\n";
            curl_easy_cleanup(curl);
        }
        std::this_thread::sleep_for(std::chrono::seconds(30));
    }
}

int main() {
    // Start ping thread
    std::thread ping_thread(keep_alive_ping);

    // Create a WebView window displaying FormatUI
    webview::webview w(true, nullptr);
    w.set_title("FormatUI");
    w.set_size(1280, 720, WEBVIEW_HINT_NONE);
    w.navigate(FORMATUI_LINK);
    w.run();

    ping_thread.join(); // Keep ping alive until window closes
    return 0;
}