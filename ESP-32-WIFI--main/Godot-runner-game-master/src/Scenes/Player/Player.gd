extends KinematicBody2D

# --- Movimento ---
const NORMAL: Vector2 = Vector2(0, -1)
const JUMP_FORCE: int = -850
const GRAVITY: int = 50

var motion: Vector2
var animation: String = "run"

# --- WebSocket / TCP ---
var txt = ""
var client
var connected: bool = false
const ip = "192.168.137.125"  # IP do ESP ou servidor TCP
const port = 80
var pulo: int = 0  # Se for 1, o personagem deve pular

func _ready():
	# Inicializa o cliente TCP
	client = StreamPeerTCP.new()
	client.connect_to_host(ip, port)
	
	if client.is_connected_to_host():
		connected = true
		print("conectado")

func _physics_process(delta: float) -> void:
	# Aplica gravidade
	motion.y += GRAVITY

	# Toca animação se necessário
	if animation != $AnimationPlayer.current_animation:
		$AnimationPlayer.play(animation)

	# Pular via teclado OU comando de rede
	if (Input.is_action_just_pressed("ui_up") or pulo == 1) and is_on_floor():
		motion.y = JUMP_FORCE
		pulo = 0  # Reseta o comando de pulo depois de usado

	# Deslizar
	if Input.is_action_pressed("ui_down") and is_on_floor():
		animation = "slide"
		$UpperBody.disabled = true
	elif $UpperBody.disabled:
		$UpperBody.disabled = false
		animation = "run"

	# Movimento
	motion = move_and_slide(motion, NORMAL)

func _process(delta: float) -> void:
	# Verifica conexão TCP
	if connected and not client.is_connected_to_host():
		connected = false
	else:
		_readWebSocket()

func _readWebSocket():
	while client.get_available_bytes() > 0:
		var message = client.get_utf8_string(client.get_available_bytes())
		if message == null:
			continue
		elif message.length() > 0:
			for i in message:
				if i == '\n':
					_messageInterpreter(txt)
					print("Recebido:", txt)
					txt = ''
				else:
					txt += i

func _messageInterpreter(txt: String):		
	var command = txt.strip_edges().split(' ')
	if command.size() >= 2:
		if command[1] == "PULAR":
			pulo = 1  # Ativa pulo na próxima física
