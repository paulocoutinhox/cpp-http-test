#include <iostream>
#include <Poco/URI.h>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/Path.h>
#include <Poco/Exception.h>
#include <sstream>

int main()
{
    try
    {
        // create the destination URI
        poco::uri uri("https://httpbin.org/anything");

        // create an HTTPS client session
        poco::net::httpsclientsession session(uri.gethost(), uri.getport());

        // prepare an HTTP GET request
        poco::net::httprequest request(poco::net::httprequest::http_get, uri.getpathandquery(), poco::net::httpmessage::http_1_1);
        request.set("user-agent", "myapp");

        // send the HTTP request
        session.sendrequest(request);

        // get the HTTP response
        poco::net::httpresponse response;

        // read and print the response header
        std::cout << "status: " << response.getstatus() << " " << response.getreason() << std::endl;
        for (const auto &header : response)
        {
            std::cout << header.first << ": " << header.second << std::endl;
        }

        // read and print the response body
        std::stringstream responsebody;
        poco::streamcopier::copystream(session.receiveresponse(response), responsebody);
        std::cout << "body:\n"
                  << responsebody.str() << std::endl;
    }
    catch (Poco::Exception &ex)
    {
        std::cerr << "Error: " << ex.displayText() << std::endl;
        return 1;
    }

    return 0;
}
