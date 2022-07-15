#include <stdio.h>
#include <conio.h>

// Definição de tipo de argumento com union
typedef union
{
	struct
	{
		unsigned char byte1;
		unsigned char byte2;
		unsigned char byte3;
		unsigned char byte4;
	};
	unsigned int value;
} my_int;

// Definição de um evento
typedef void (*event_example)(my_int arg);

// Definição classe com evento
class EventClass
{
	private:
		event_example trigger_event; // Declaração do evento
		
	public:
		// Adiciona evento a classe
		void onEvent(event_example ev) 
		{
			trigger_event = ev;
		}
		
		// Dispara evento
		void event(my_int value) 
		{
			trigger_event(value);
		}
};

// Execução do evento
void do_this_on_event(my_int args)
{
	printf("event: %06d= 0x%02x 0x%02x 0x%02x 0x%02x\n", args, args.byte4, args.byte3, args.byte2, args.byte1);	
}

// Exemplo de disparo do evento.
static void event_task(void *p)
{
	EventClass *event = (EventClass *)p;
	my_int value;
	value.value = 420001;
	event->event(value);
}

// programa principal
main()
{
	EventClass eventObject;
	eventObject.onEvent(do_this_on_event);
	for (int i=1; i<=10; i++)
	{
		my_int tmp;
		tmp.value = i;
		eventObject.event(tmp);
	} 
	event_task(&eventObject);
	getch();
}
