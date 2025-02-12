# Dasu!

_**Dasu**_ is a cli program that allow excuting commands with elevated privileges (similar to `sudo` or `doas`). This program design to be simple and just for fun!

> [!WARNING]
> Do not use DASU for everyday or serious use. 

## Buiding and usage

* Install meson and ninja.
* In the repository, run `meson setup build`.
* `cd` to the `build` directory and run `ninja`.
* now you need to grant `6755` permissions to `dasu`:

```sh
sudo chown root:root ./dasu  # sudo :))
sudo chmod 6755 ./dasu
```

Thats it! Now you can run `dasu` like `sudo`, you can install `dasu` at your own risk:
```sh
./dasu ninja install
```

License? MIT

Wanna countribute? Feel free! 
