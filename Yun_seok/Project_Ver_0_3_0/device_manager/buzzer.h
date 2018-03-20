#define MAGIC 'k'
#define MAXNR 6

struct pwm_duty_t {
		int pulse_width;		// nsec
			int period;			// nsec
};

#define BUZZER_OFF	_IO(MAGIC,0)
#define BUZZER_ON	_IO(MAGIC,1)
