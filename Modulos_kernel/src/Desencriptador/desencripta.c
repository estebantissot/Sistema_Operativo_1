#include<linux/module.h>
#include<linux/string.h>
#include<linux/fs.h>
#include<asm/uaccess.h>

#define FILE_NAME "dispositivo"

static char msg[100] = {0};
static short readPos = 0;

static int dev_open(struct inode *, struct file *);
static int dev_rls(struct inode *, struct file *);
static ssize_t dev_read(struct file*, char*, size_t, loff_t*);
static ssize_t dev_write(struct file*, char*,const size_t, loff_t*);

static struct file_operations fops = 
{
	.read = dev_read,
	.open = dev_open,
	.write = dev_write,
	.release = dev_rls
};

int init_module(void)
{//Esta funcion se ejecuta al cargar el modulo
	int t = register_chrdev(88,FILE_NAME,&fops);
	if(t<0) printk(KERN_ALERT "Fallo la carga del modulo desencripta\n");
	else printk(KERN_ALERT "La carga del modulo desencripta fue un exito.\n");

	return t;
}

void cleanup_module(void) 
{ //Esta funcion se ejecuta al descargar el modulo
	unregister_chrdev(89,FILE_NAME);
	printk(KERN_ALERT "La descarga del modulo desencripta fue un exito.\n");
}

static int dev_open(struct inode *inod, struct file *fil)
{
	printk(KERN_ALERT "Se abrio el dispositivo\n");
	return 0;
}

static ssize_t dev_read(struct file *filp, char *buff, size_t len, loff_t *off)
{
	short count = 0;
	while(len && (msg[readPos]!=0))
	{
		put_user(msg[readPos]-(char) 10,buff++); //se desplazan 10 para recuperar el caracter original
		count++;
		len--;
		readPos++;
	}
	return count;
}


static ssize_t dev_write(struct file *filp, char *buff, size_t len, loff_t *off)
{
	short count = 0;
	memset(msg,0,100);
	readPos = 0;
	while(len > 0)
	{
		msg[count] = buff[count];
		count++;
		len--;
	}
	return count;
}

static int dev_rls(struct inode *inod, struct file *fil)
{
	printk(KERN_ALERT "El dispositivo fue cerrado con exito\n");
	return 0;
}
