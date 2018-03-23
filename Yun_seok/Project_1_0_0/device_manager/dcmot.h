#define MAGIC 'k'
#define MAXNR 6

struct pwm_duty_t {
	int pulse_width;	
	int period;			
};

#define DC_STOP _IO(MAGIC,0)
#define DC_GO _IO(MAGIC,1)
#define DC_BACK _IO(MAGIC,2)
