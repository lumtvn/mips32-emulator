struct etype
{
	int n_arg;
	char *entry;
	char *command;
	char *arg[];
};


void runenv(struct etype *env);
void restart(struct etype *env);
struct etype *parseentry(struct etype *env);
void analize(struct etype *env);
void strip(char *s);

