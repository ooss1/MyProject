#define MAGIC 'k'
#define MAXNR 6

struct pwm_duty_t {
		int pulse_width;		// nsec
			int period;			// nsec
};

#define BUZZER_OFF		0
#define BUZZER_ON		1
