
#include "./Network.hpp"

void Network::get(const std::string& url)
{
    ostringstream stream;
    // We are going to put the request's output in the previously declared stream
    curl_ios<ostringstream> ios(stream);

    // Declaration of an easy object
    curl_easy easy(ios);

    // Add some option to the curl_easy object.
    easy.add<CURLOPT_URL>(url.c_str());
    easy.add<CURLOPT_FOLLOWLOCATION>(1L);

    try {
        easy.perform();

		// Retrieve information about curl current session.
		auto x = easy.get_info<CURLINFO_CONTENT_TYPE>();

		/**
		 * get_info returns a curl_easy_info object. With the get method we retrieve
		 * the std::pair object associated with it: the first item is the return code of the
		 * request. The second is the element requested by the specified libcurl macro.
		 */
		std::cout<<x.get()<<std::endl;

    } catch (curl_easy_exception &error) {
		// If you want to print the last error.
		std::cerr<<error.what()<<std::endl;

		// If you want to print the entire error stack you can do
		error.print_traceback();
    }
}