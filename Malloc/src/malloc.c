#include <sys/types.h>
#include <unistd.h>


/*
Es necesario que los punteros esten alineados con el tamaño del entero.
Consideramos el caso de 4bytes(32 bits).
La estructura de meta-data tiene tres campos de 4bytes cada uno.
Para que el puntero tenga 4bytes usamos un preprocesador macro, de esta
forma el puntero va a ser multipo de 4. 
*/


//Definimos un macro para que el tamaño del dato sea de 4 bytes 
#define align4(x) (((((x)-1)>>2)<<2)+4) 

//Definimos un macro para mantener el tamaño del bloque de meta-data
#define BLOCK_SIZE sizeof(struct s_block)

typedef struct s_block * t_block; //bloque de meta-data(32bits)

struct s_block
{
	size_t size; //indica el tamaño
	t_block next; //enlaza al siguiente bloque de memoria
	struct s_block *prev;
	void *ptr;
	int free; //indica si el bloque esta libre
	char data[1]; //evita que la longitud de la matriz sea cero, C no lo permite.
};


/*ubica el punto break en la direccion pasada como parametro
devuelve 0 si fue exitoso
devuelve -1 si hubo error*/
//int brk(const void *addr);


/*mueve el break incrementando en los bytes pasados como parametro.
si el parametro es 0 debe devolver la direccion actual del break*/
//void *sbrk(intptr_t incr); 

void split_block(t_block b, size_t s);
t_block extend_heap(t_block last, size_t s);
t_block fusion(t_block b);
t_block get_block(void *p);
t_block first_fit(t_block *last , size_t size); //Politica del primer ajuste
t_block best_fit(t_block *last , size_t size); //Politica del mejor ajuste
t_block next_fit(t_block *last, size_t size); //Politica del proximo ajuste
t_block worst_fit(t_block *last, size_t size); //Politica del peor ajuste
void *malloc(size_t);
void free(void *p);
t_block base=NULL; //puntero global
t_block last_used=NULL;
int valid_addr(void *p);

//Funcion principal
int main(int argc, char **argv)
{
	return(EXIT_SUCCESS);
}


/*Esta funcion extiende la heap, para ello movemos el break e 
inicializamos un nuevo bloque, luego actualizamos el "next field"
del ultimo bloque de la heap*/
t_block extend_heap(t_block last, size_t s)
{
	t_block b;
	b=sbrk(0);
	if(sbrk(BLOCK_SIZE+s) == (void*)-1)
		return (NULL);
	b->size=s;
	b->next=NULL;
	if(last)
		last->next=b;
	b->free=0;
	return(b);
}


/*Esta funcion busca un espacio suficientemente grande.
Retorna el fragmento o NULL si no encuentra ninguno.
base es un puntero global al punto de partida de nuestra heap
Despues de la ejecucion posisionamos a b en el ultimo
fragmento visitado para que la funcion malloc pueda extederse 
fasilmente.*/
t_block find_block(t_block *last, size_t size)
{
	t_block b=base;
	while(b && !(b->free && b->size >= size))
	{
		*last=b;
		b=b->next;
	}
	return (b);
}


/*Esta funcion se llama solo si hay espacio disponible. 
Divide el bloque de datos para tener el tamaño deseado.*/
void split_block(t_block b, size_t s)
{
	t_block new;
	new = b->data+s;
	new->size = b->size - s - BLOCK_SIZE;
	new->next = b->next;
	new ->free = 1;
	b->size = s;
	b->next = new;
}


/*Esta funcion se utiliza despues de cada malloc. 
Si el siguiente fragmento esta libre lo sumamos 
al fragmento que queda libre, despues de la 
division, y tambien sumamos el tamaño del meta-data.*/
t_block fusion(t_block b)
{
	if(b->next && b->next ->free)
	{
		b->size += BLOCK_SIZE + b->next ->size;
		b->next = b->next ->next;
		if (b->next)
			b->next ->prev = b;
	}
	return (b);
}

//Retorna el bloque de la direccion que queremos liberar
t_block get_block(void *p)
{
	char *tmp;
    tmp = p;
    return (p = tmp -= BLOCK_SIZE );
}


//Verifica la direccion que queremos liberar
int valid_addr(void *p)
{
	if (base)
	{
        if ( p>base && p< sbrk (0))
            return (p == ( get_block (p))->ptr );
    }
    return (0);
}



/*Algoritmo de la funcion malloc:
-busca un bloque lo suficientemente grande
-si base esta inicializado:
	-trata de dividir el bloque
	-marca el fragmento como usado
-si base no esta inicializado extiende la heap
si la funcion falla devolvemos NULL*/
void *malloc(size_t size)
{
	t_block b,last;
	size_t s;
	s = align4(size);
	if(base) 
	{
		/* First find a block */
		last = base;
		 b = first_fit (&last ,s);   // politica del primer ajuste
    	//b = best_fit  (&last ,s);  // politica el mejor ajuste
    	//b = next_fit  (&last ,s);  // politica del proximo ajuste
    	//b = worst_fit (&last ,s);  // politica del peor ajuste  
            
    // b es el bloque que podemos remplazar o es null en caso que no haya ningun bloque con el tamaña suficiente sin usar
		if(b) {
			last_used=b; 
			/* can we split */
			if ((b->size - s) >= (BLOCK_SIZE + 4))
				split_block (b,s);
			b->free =0;
		}
		else
		{
			/* No fitting block , extend the heap */
			b = extend_heap (last,s);
			if(!b)
				return (NULL);
		}
	} 
	else 
	{
		/* first time */
		b = extend_heap (NULL,s);
		if(!b)
			return (NULL);
		base = b;
	}
	return (b->data);
}


/*Funcion calloc:
	-Reserva espacio de memoria llamando a malloc
	-rellena todo el bloque con 0*/
void *calloc(size_t number, size_t size)
{
	size_t *new;
	size_t s4,i;
	new = malloc(number *size);
	if (new) 
	{
		s4 = align4(number *size) << 2;
		for (i=0; i<s4; i++)
			new[i] = 0;
	}
	return (new);
}


/*
La funcion free libera memoria. Esto se hace poniendo 
el break, llamada a la funsion brk() en la posicion del 
fragmento si estamos al final de la heap. 
Algoritmo:
-si el puntero es valido:
	-recibimos la direccion del bloque
	-lo marcamos como libre
	-si el anterior existe y esta libre, retrocedemos 
	y fusionamos ambos bloques.
	-si estamos en el ultimo bloque liberamos memoria
	-si no hay mas bloques volvemos al estado original(base=NULL)
-si el puntero no es valido no hacemos nada.
*/
void free(void *p)
{
	t_block b;
	if (valid_addr(p))
	{
		b = get_block(p);
		b->free = 1;
		/* fusion with previous if possible */
		if(b->prev && b->prev ->free)
			b = fusion (b->prev);
		/* then fusion with next */
		if(b->next)
			fusion(b);
		else
		{
			/* free the end of the heap */
			if(b->prev)
				b->prev ->next = NULL;
			else
				/* No more block !*/
				base = NULL;
			brk(b);
		}
	}
}

//========================== Politicas de Ajuste ==========================//

//Se busca y utiliza el primer lugar en memoria libre y con tamaño suficiente
t_block first_fit ( t_block *last , size_t size )
{
    t_block b=base;     // Empezamos del primer lugar de memoria reservado       
    while (b && !(b->free && b->size >= size ))
    {  
        *last = b;      // voy guardando el ultima espacio visitado
        b = b->next;    // nos vamos moviendo entre la memorias encadenadas
    }
    return (b);//retorno el espacio que podemos utilizar
}

/*Se busca el segmento de memoria libre utilizable de tamaño mas parecido o que 
deje menor memoria sin utilizar dentro del mismo segmento*/
t_block best_fit(t_block *last , size_t size)
{
    t_block b=base;      //Empezamos del primer lugar de memoria reservado
    t_block mejor=NULL;  //Vamos a guardar el segmento que mas se ajuste a nuestro tamaño
    size_t minimo=-1;      
    while(b)
    {
        *last=b;        // voy guardando el ultimo espacio visitado
        if((b->free)&&(b->size >= size)&&(minimo>b->size-size))// si el bloque esta libre, cumple con el tamaño requerido y la porcion de segmento que queda es menor a la anterio registrada
        {    
            minimo=b->size-size;// vamos registrando la menor diferencia de memoria entre los bloques
            mejor=b;           //guardamos ese bloque ya que el que mejor se ajusta al tamaño que requerimos
        }
        b=b->next;      // avanzamos hasta llegar al ultimo segmento
    }
    
    return(mejor);      // retorno el mejor ajuste
}

/*Se busca el espacio de memoria que cumplan con el minimo de tamaño que requerimos
 pero empezamos a buscar del ultimo segmento de memoria que modificamos*/
t_block next_fit(t_block *last, size_t size)
{
    t_block b=last_used;
    int flag=0;
    do
    {
        if(flag==0)
        	*last = b;   // voy guardando el ultima espacio visitado
        b = b->next;           // nos vamos moviendo entre la memorias encadenadas
        
        if(b==NULL)
        {
            b=base;            // en caso de haber llegado al ultimo lugar de memoria asignada volvemos al primero, la bandera nos sirve para mantener el ultimo segmento antes que empieze la memoria no asignada.
            flag=1;           // ya que el mismo despues va a ser utilizado si necesitamos correr el break
        }   
                                      
        if(b==last_used)
        	b=NULL;    // si dimos la vuelta completa y no encontramos un espacio adecuado, retornamos null
    }
    while ((b!=last_used)&& !(b->free && b->size >= size));
    return(b);
}

/*Se busca cual es el segmento de memoria libre utilizable que deje mayor 
espacio sin utilizar dentro del mismo segmento*/
t_block worst_fit(t_block *last, size_t size)
{
   t_block b=base;         //Empezamos del primer lugar de memoria reservado
   t_block peor=NULL;    //Vamos a guardar el segmento que mas se ajuste a nuestro tamaño
   size_t max=0;      
   while(b)
   	{
        *last=b;        // voy guardando el ultimo espacio visitado
        if((b->free)&&(b->size >= size)&&(max<b->size-size))// si el bloque esta libre, cumple con el tamaño requerido y la porcion de segmento que queda es menor a la anterio registrada
        {    
            max=b->size-size;  // vamos registrando la mayor diferencia de memoria entre los bloques
            peor=b;            //guardamos ese bloque ya que el que mejor se ajusta al tamaño que requerimos
        }
        b=b->next;      // avanzamos hasta llegar al ultimo segmento
    }
    return(peor);     
}
