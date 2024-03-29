#include <stdio.h>
#include <conio.h>

// Definição de tipo de argumento com union
typedef union {
    struct {
        unsigned char byte1;
        unsigned char byte2;
        unsigned char byte3;
        unsigned char byte4;
    };
    unsigned int value;
} my_int;

// Definição de um tipo de função para eventos
typedef void (*event_example)(my_int arg);

// Definição da classe com evento
class EventClass {
private:
    event_example trigger_event; // Ponteiro para a função do evento

public:
    // Método para associar uma função de evento à classe
    void onEvent(event_example ev) {
        trigger_event = ev;
    }

    // Método para disparar o evento
    void event(my_int value) {
        if (trigger_event != nullptr) // Verifica se a função do evento está definida
            trigger_event(value);
    }
};

// Função a ser executada quando o evento ocorre
void do_this_on_event(my_int args) {
    printf("Evento: %06d = 0x%02x 0x%02x 0x%02x 0x%02x\n", args.value, args.byte4, args.byte3, args.byte2, args.byte1);
}

// Função para simular uma tarefa que dispara o evento
static void event_task(void *p) {
    EventClass *event = (EventClass *)p;
    my_int value;
    value.value = 420001;
    event->event(value);
}

// Função principal
int main() {
    EventClass eventObject;

    // Associando a função do evento à classe
    eventObject.onEvent(do_this_on_event);

    // Disparando o evento várias vezes com diferentes valores
    for (int i = 1; i <= 10; i++) {
        my_int tmp;
        tmp.value = i;
        eventObject.event(tmp);
    }

    // Simulando uma tarefa que dispara o evento
    event_task(&eventObject);

    // Aguardando entrada do usuário antes de sair
    getch();
    return 0;
}
