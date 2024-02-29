
# la doc de kalos

## types
`kalos_int`

	uint64 if 64 bits
	uint32 if 32 bits


`kalos_events_t`

	key : char[5] representing the key as a utf-8 char
	is_pressed : 
				0 : key is released
				1 : key is pressed
				2 : indicate end of the events
				3 : special key pressed
				4 : special key released

### special keys:
special keys are stored in `.key[0]`
```
escape
ctrl left
ctrl right
alt
arrow up
arrow down
arrow left
arrow right
enter / return
erase
shift (left or right)
```
## events
	kalos_events : buffer for the events


`void kalos_update_events()`

	update the events and write them in kalos_events buffer

`kalos_int kalos_get_time_ms()`

	return a time in miliseconds that can be compared for delay
	(generaly just unix time)
	(does not guarantee to be the time and date of now)

## initialisation / ending

`kalos_int kalos_init()`

	must be called before anything done with kalos
	it will initialize things for the lib
	will return a kalos_int depending on succes or not

`void kalos_end()`

	tell the library that everythings is finished
	it will free allocations and do what it has to do
## drawing 

`drawing buffer` 

	a buffer containing the pixel drawn by the functions
	it has always the same size as the window
	(only the library should interact with it directly)

every drawing has to be done in the drawing buffer and not on the window directly
when a function to draw is called it will draw on the buffer not on the window,
to see the modification on the window use `kalos_update_window` function


`void kalos_update_window()`

	blit the drawing buffer to the window


`void kalos_set_pixel(int x, int y, char r, char g, char b)s`

	set a pixel at (x, y) to the color (r, g, b) in RGB

`void kalos_fill_window(char r, char g, char b)`

	set every pixel of the window to (r, g, b) in RGB


`void kalos_fill_rect(int x, int y, int w, int h char r, char g, char b)`

	set every pixel in rectangle at top-left corner (x, y) 
	and with w, height h to (r, g, b) in RBG








