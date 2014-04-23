function long2ip(ip) {
  //  discuss at: http://phpjs.org/functions/long2ip/
  // original by: Waldo Malqui Silva
  //   example 1: long2ip( 3221234342 );
  //   returns 1: '192.0.34.166'

  if (!isFinite(ip))
    return false;

  return [ip >>> 24, ip >>> 16 & 0xFF, ip >>> 8 & 0xFF, ip & 0xFF].join('.');
}

function ip2long(IP) {
  //  discuss at: http://phpjs.org/functions/ip2long/
  // original by: Waldo Malqui Silva
  // improved by: Victor
  //  revised by: fearphage (http://http/my.opera.com/fearphage/)
  //  revised by: Theriault
  //   example 1: ip2long('192.0.34.166');
  //   returns 1: 3221234342
  //   example 2: ip2long('0.0xABCDEF');
  //   returns 2: 11259375
  //   example 3: ip2long('255.255.255.256');
  //   returns 3: false

  var i = 0;
  // PHP allows decimal, octal, and hexadecimal IP components.
  // PHP allows between 1 (e.g. 127) to 4 (e.g 127.0.0.1) components.
  IP = IP.match(
    /^([1-9]\d*|0[0-7]*|0x[\da-f]+)(?:\.([1-9]\d*|0[0-7]*|0x[\da-f]+))?(?:\.([1-9]\d*|0[0-7]*|0x[\da-f]+))?(?:\.([1-9]\d*|0[0-7]*|0x[\da-f]+))?$/i
  ); // Verify IP format.
  if (!IP) {
    // Invalid format.
    return false;
  }
  // Reuse IP variable for component counter.
  IP[0] = 0;
  for (i = 1; i < 5; i += 1) {
    IP[0] += !! ((IP[i] || '')
      .length);
    IP[i] = parseInt(IP[i]) || 0;
  }
  // Continue to use IP for overflow values.
  // PHP does not allow any component to overflow.
  IP.push(256, 256, 256, 256);
  // Recalculate overflow of last component supplied to make up for missing components.
  IP[4 + IP[0]] *= Math.pow(256, 4 - IP[0]);
  if (IP[1] >= IP[5] || IP[2] >= IP[6] || IP[3] >= IP[7] || IP[4] >= IP[8]) {
    return false;
  }
  return IP[1] * (IP[0] === 1 || 16777216) + IP[2] * (IP[0] <= 2 || 65536) + IP[3] * (IP[0] <= 3 || 256) + IP[4] * 1;
}


function buildIpRange(ip_with_range)
{
    var ip_match = ip_with_range.match(/^([0-9\.]+)\/([0-9]+)$/);
    if (ip_match == null) {
        return null;
    }

    var ip = ip_match[1];
    var range = ip_match[2];

    var start = ip2long(ip);
    var ip_count = 1 << (32 - range);

    var internal_ips = new Array();

    for (iterator = 0; iterator < ip_count; iterator++) {
        internal_ips.push(start + iterator);
    }

    internal_ips.sort();

    internal_ips = internal_ips.map(long2ip);

    return internal_ips.join("\n");
}