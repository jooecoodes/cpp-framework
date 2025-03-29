#include <iostream>
#include <fmt/core.h>
#include <nlohmann/json.hpp>
#include <curl/curl.h>

using json = nlohmann::json;

// Callback function to store response from curl
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}


int main(int, char**){
    std::cout << "Hello, from pkg-test!\n";
    fmt::print("Hello, from pkg-test! and fmt\n");
    std::cout << "Hello Again\n";
    std::cout << "Hello Again\n";

    json data = {{"name", "Alice"}, {"age", 25}, {"is_student", false}};
    std::cout << "JSON Output: " << data.dump(4) << std::endl;


    
    // CURL API fetching demonstration, this uses SLL tho 
    CURL* curl;
    CURLcode res;
    std::string response_data;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://official-joke-api.appspot.com/random_joke");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        curl_easy_cleanup(curl);
    }

    try {
        json joke = json::parse(response_data);
        std::cout << "Here's a joke for you: \n";
        std::cout << joke["setup"] << std::endl;
        std::cout << joke["punchline"] << std::endl;
    } catch (json::parse_error& e) {
        std::cerr << "JSON Parsing Error: " << e.what() << std::endl;
    }

    
    return 0;
}
