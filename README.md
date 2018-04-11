# UDP logger

Sniff for UDP logging packets. Maybe overkill for this purpose but works well.

Requires root priviledges for promiscuous monitoring.

### Debugging

```sh
# clear local dns cache
sudo systemd-resolve --flush-caches
```

### Link

```sh
cd /bin
ln -sf /home/jeffrey/router/udplog/udp udplog
```

### Resources

* [lambdas](https://msdn.microsoft.com/en-us/library/dd293608.aspx)







#### end
