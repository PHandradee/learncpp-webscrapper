#include "cpr/auth.h"
#include <cstddef>
#include <iostream>
#include <cstring>
#include <lexbor/html/parser.h>
#include <cpr/cpr.h>

int main()
{
    // HTML a ser analisado
    const char* html = "<html><head><title>Meu Título</title></head><body>Conteúdo do corpo</body></html>";

    // Criação do documento HTML
    lxb_html_document_t* document = lxb_html_document_create();
    if (document == nullptr) {
        std::cerr << "Erro ao criar o documento HTML" << std::endl;
        return 1;
    }

    // Realiza o parse do HTML
    lxb_status_t status = lxb_html_document_parse(document, reinterpret_cast<const lxb_char_t*>(html), std::strlen(html));
    if (status != LXB_STATUS_OK) {
        std::cerr << "Erro ao fazer o parse do HTML" << std::endl;
        return 1;
    }

    size_t title_buffer {};
    // Obtém o título do documento
    const lxb_char_t* title = lxb_html_document_title(document, &title_buffer);
    std::cout << "Título do documento: " << title << std::endl;

    // Libera a memória
    lxb_html_document_destroy(document);


    cpr::Response r = cpr::Get(cpr::Url{"https://api.github.com/repos/whoshuu/cpr/contributors"},
                      cpr::Authentication{"user", "pass", cpr::AuthMode::BASIC},
                      cpr::Parameters{{"anon", "true"}, {"key", "value"}});
    std::cout << r.status_code << '\n';                  // 200
    std::cout << r.header["content-type"] << '\n';       // application/json; charset=utf-8
    std::cout << r.text << '\n';                         // JSON text string
    
    return 0;
}
