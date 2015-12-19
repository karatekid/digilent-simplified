# Digilent Simplified

A C++ wrapper around Digilent's [Waveforms SDK](https://www.digilentinc.com/Products/Detail.cfm?Prod=WAVEFORMS),
which targets the [Digilent Analog Discovery](http://www.digilentinc.com/Products/Detail.cfm?Prod=ANALOG-DISCOVERY).

## Getting Started

### Installation Instructions for Linux

1. You'll need to install the Waveforms SDK by downloading the appropriate package
[here](https://www.digilentinc.com/Products/Detail.cfm?Prod=WAVEFORMS).
2. Run `sudo make install`

To perform a test you can run `sudo make test`, just make sure that you set your
`LD_LIBRARY_PATH` properly. The installation puts a shared object file in
`/usr/local/lib`, so you can add it to your path by putting something like this
in your config file:

```
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
```

## Documentation

