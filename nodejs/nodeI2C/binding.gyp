{
  "targets": [
    {
      "target_name": "rI2C",
      "sources": [ "i2c.c", "addon.cc" ],
      "link_settings" : { "libraries" : [ "-lwiringPi" ] }
    }
  ]
}
