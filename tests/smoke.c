#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <brainfuck.h>

static unsigned char output_buffer[16];
static size_t output_length;

static int capture_output(int chr) {
    if (output_length < sizeof(output_buffer)) output_buffer[output_length++] = (unsigned char) chr;
    return chr;
}

int main() {
    BrainfuckState *state = brainfuck_state();
    BrainfuckExecutionContext *context = brainfuck_context(BRAINFUCK_TAPE_SIZE);
    BrainfuckInstruction *instruction = brainfuck_parse_string("++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.++"
                                                               "+.------.--------.>>+.>++.");
    brainfuck_add(state, instruction);
    brainfuck_execute(state->root, context);
    brainfuck_destroy_context(context);
    brainfuck_destroy_state(state);

    output_length = 0;
    context = brainfuck_context(32);
    context->output_handler = capture_output;
    state = brainfuck_state();
    instruction = brainfuck_parse_string("+1.+10.-3.");
    brainfuck_add(state, instruction);
    brainfuck_execute(state->root, context);
    assert(output_length == 3);
    assert(output_buffer[0] == 1);
    assert(output_buffer[1] == 11);
    assert(output_buffer[2] == 8);
    assert(context->tape_accesses[0] == 6);
    assert(context->total_tape_accesses == 6);
    brainfuck_destroy_context(context);
    brainfuck_destroy_state(state);
    return EXIT_SUCCESS;
}
