#ifndef MIDI_H
#define MIDI_H
#include <inttypes.h>

#include "config.h"

#ifndef MIDI_VOICES
#error MIDI_VOICES is not defined
#endif

// Base wave
#define MIDI_BASE_WAVE    56

// Amplifier envelope controls
#define MIDI_AMP_ATTACK   60
#define MIDI_AMP_SUSTAIN  61
#define MIDI_AMP_RELEASE  62
#define MIDI_AMP_ASR      63

// Modulation envelope controls
#define MIDI_MOD_ATTACK   64
#define MIDI_MOD_SUSTAIN  65
#define MIDI_MOD_RELEASE  66
#define MIDI_MOD_ASR      67
#define MIDI_MOD_EG_INT   68

#define MIDI_GATE_ON_BIT   1
#define MIDI_GATE_TRIG_BIT 2

typedef struct midi_voice
{
	uint8_t note;
	uint8_t velocity;
	uint8_t gate;
	int8_t age;
} midi_voice;

typedef struct midi_status
{
	// Internal state of the interpreter
	uint8_t dlim;
	uint8_t dcnt;
	uint8_t status;
	uint8_t channel;
	uint8_t dbuf[4];

	// Per voice controls
	midi_voice voices[MIDI_VOICES];

	// Basic MIDI controls
	uint8_t program;
	uint16_t pitchbend;
	uint8_t reset;

	// Callbacks
	void (*program_change_handler)(uint8_t program);
	void (*control_change_handler)(uint8_t index, uint8_t value);

	// MIDI controllers
	uint8_t control[128];
} midi_status;

extern void midi_init(midi_status *midi);
extern void midi_process_byte(midi_status *midi, uint8_t byte, uint8_t channel);

#endif