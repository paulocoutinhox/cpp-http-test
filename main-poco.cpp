#include <iostream>
#include <Poco/URI.h>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/Path.h>
#include <Poco/Exception.h>
#include <sstream>

int main() {
    try {
        // Criar a URI do destino
        Poco::URI uri("https://reqbin.com/echo");

        // Criar uma sessão de cliente HTTPS
        Poco::Net::HTTPSClientSession session(uri.getHost(), uri.getPort());

        // Preparar uma solicitação HTTP GET
        Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET, uri.getPathAndQuery(), Poco::Net::HTTPMessage::HTTP_1_1);
        request.set("User-Agent", "MyApp");

        // Enviar a solicitação HTTP
        session.sendRequest(request);

        // Obter a resposta HTTP
        Poco::Net::HTTPResponse response;

        // Ler e imprimir o cabeçalho da resposta
        std::cout << "Status: " << response.getStatus() << " " << response.getReason() << std::endl;
        for (const auto& header : response) {
            std::cout << header.first << ": " << header.second << std::endl;
        }

        // Ler e imprimir o corpo da resposta
        std::stringstream responseBody;
        Poco::StreamCopier::copyStream(session.receiveResponse(response), responseBody);
        std::cout << "Body:\n" << responseBody.str() << std::endl;
    }
    catch (Poco::Exception& ex) {
        std::cerr << "Error: " << ex.displayText() << std::endl;
        return 1;
    }

    return 0;
}
