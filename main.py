import serial
import time
import json
import os
from aiogram import Bot, types
from aiogram.dispatcher import Dispatcher
from aiogram.utils import executor
from threading import Thread
from picamera import PiCamera

API_TOKEN = "ur bot token"

bot = Bot(token=API_TOKEN)
dp = Dispatcher(bot)

arduino = serial.Serial("/dev/ttyACM0", 9600, timeout=1)
arduino.flush()

camera = PiCamera()
camera.resolution = (1080, 1920)


def make_image():
    camera.capture("/home/pi/Desktop/watering/image.jpg")


def remove_image():
    if os.path.isfile("/home/pi/Desktop/watering/image.jpg"):
        os.remove("/home/pi/Desktop/watering/image.jpg")


def make_message(watch, get):
    return "{{\"watch\":{},\"get\":{}}}".format(watch, get)


def watch_loop():
    while True:
        arduino.write(make_message(time.strftime("%H%M"), "false").encode("utf-8"))
        time.sleep(60 - int(time.strftime("%S")))


def get_sensors():
    arduino.write(make_message(time.strftime("%H%M"), "true").encode("utf-8"))
    time.sleep(1)
    return json.loads(arduino.readline().decode("utf-8").rstrip())


@dp.message_handler(commands=["start"])
async def start_command(message: types.Message):
    keyboard = types.ReplyKeyboardMarkup(resize_keyboard=True)
    keyboard.add("/help", "/info", "/photo")
    await bot.send_message(message.chat.id, "Hello, this is a smart watering bot", reply_markup=keyboard)


@dp.message_handler(commands=["help"])
async def help_command(message: types.Message):
    await bot.send_message(message.chat.id, "Write the /info command to get the sensor readings\n"
                                            "Write the /photo command to get a photo from the camera")


@dp.message_handler(commands=["info"])
async def info_command(message: types.Message):
    await bot.send_message(message.chat.id, "\n".join((f"{key}: {value}" for key, value in get_sensors().items())))


@dp.message_handler(commands=["photo"])
async def photo_command(message: types.Message):
    make_image()
    await bot.send_photo(message.chat.id, types.InputFile("/home/pi/Desktop/watering/image.jpg"))
    remove_image()


if __name__ == '__main__':
    print("Beginning...", end=" ")
    time.sleep(5)
    print("it works!")
    Thread(target=watch_loop).start()
    executor.start_polling(dp)
