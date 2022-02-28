#ifndef __MESSAGE_H_
#define __MESSAGE_H_

#include <stdint.h>
typedef uint16_t neomessagetype_t;

#ifdef __cplusplus

#include "icsneo/communication/network.h"
#include <vector>

namespace icsneo {

class Message {
public:
	enum class Type : neomessagetype_t {
		Frame = 0,

		CANErrorCount = 0x100,

		// Past 0x8000 are all for internal use only
		Invalid = 0x8000,
		RawMessage = 0x8001,
		ReadSettings = 0x8002,
		ResetStatus = 0x8003,
		DeviceVersion = 0x8004,
		Main51 = 0x8005,
		FlexRayControl = 0x8006,
		EthernetPhyRegister = 0x8007,
		LogicalDiskInfo = 0x8008,
	};

	Message(Type t) : type(t) {}
	virtual ~Message() = default;
	const Type type;
	uint64_t timestamp = 0;
};

class RawMessage : public Message {
public:
	RawMessage(Message::Type type = Message::Type::RawMessage) : Message(type) {}
	RawMessage(Message::Type type, Network net) : Message(type), network(net) {}
	RawMessage(Network net) : Message(Message::Type::RawMessage), network(net) {}
	RawMessage(Network net, std::vector<uint8_t> d) : Message(Message::Type::RawMessage), network(net), data(d) {}

	Network network;
	std::vector<uint8_t> data;
};

class Frame : public RawMessage {
public:
	Frame() : RawMessage(Message::Type::Frame) {}

	uint16_t description = 0;
	bool transmitted = false;
	bool error = false;
};

}

#endif // __cplusplus

#ifdef __ICSNEOC_H_

#define ICSNEO_MESSAGE_TYPE_FRAME (0x0)
#define ICSNEO_MESSAGE_TYPE_CAN_ERROR_COUNT (0x100)
#define ICSNEO_MESSAGE_TYPE_INVALID (0x8000)
#define ICSNEO_MESSAGE_TYPE_RAW_MESSAGE (0x8001)
#define ICSNEO_MESSAGE_TYPE_READ_SETTINGS (0x8002)
#define ICSNEO_MESSAGE_TYPE_RESET_STATUS (0x8003)
#define ICSNEO_MESSAGE_TYPE_DEVICE_VERSION (0x8004)
#define ICSNEO_MESSAGE_TYPE_MAIN51 (0x8005)
#define ICSNEO_MESSAGE_TYPE_FLEXRAY_CONTROL (0x8006)

#endif // __ICSNEOC_H_

#endif