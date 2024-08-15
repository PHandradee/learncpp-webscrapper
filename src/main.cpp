#include <cstddef>
#include <iostream>
#include <cstring>
#include <lexbor/html/parser.h>

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

    return 0;
}
