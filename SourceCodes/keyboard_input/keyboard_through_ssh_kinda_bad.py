from sshkeyboard import listen_keyboard

def press(key):
    #print(f"'{key}' pressed")
    if key == 'right':
        print('r pressed')
    if key == 'left':
        print('l pressed')
    if key == 'up':
        print('u pressed')
    if key == 'down':
        print('d pressed')

def release(key):
    #print(f"'{key}' released")
    if key == 'right':
        print('r released')
    if key == 'left':
        print('l released')
    if key == 'up':
        print('u released')
    if key == 'down':
        print('d released')

listen_keyboard(
    on_press=press,
    on_release=release,
)
