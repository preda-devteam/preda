export const MINUTE = 60 * 1000;
export const HOUR = MINUTE * 60;
export const DAY = HOUR * 24;
export const WEEK = 7 * DAY;
export const MONTH = DAY * 30;
export const PERMANENT = MONTH * 2;

// convert yyyymmdd to dd/mm/yyyy
export function formatDate(date: any) {
  const year = `${date}`.slice(0, 4);
  const month = `${date}`.slice(4, 6);
  const day = `${date}`.slice(6);
  return `${parseInt(day, 10)}/${parseInt(month, 10)}/${parseInt(year, 10)}`;
}

// Return to the dead time of today, the unit is second
export function getTodayEndUnixTime(): number {
  const t = new Date();
  return new Date(t.getFullYear(), t.getMonth(), t.getDate(), 23, 59, 59).getTime() / 1000;
}

function datetime2Timestamp(datetime: string) {
  return new Date(datetime).getTime();
}

export function padStart(num: any, len: number = 2, ch: string = '0'): string {
  let output = `${num}`;

  while (output.length < len) {
    output = `${ch}${output}`;
  }
  return output;
}

// Whether the current time point is within the given start date and the end date range
export function checkCurrentTimeInRangeDate(start: string, end: string): boolean {
  const now = new Date().getTime();
  const startTimestamp = datetime2Timestamp(`${start} 00:00`);
  const endTimestamp = datetime2Timestamp(`${end} 23:59`);
  return now >= startTimestamp && now <= endTimestamp;
}

// start, end shown in seconds
export function checkCurrentTimeInRangeDatetime(start: any, end: any): boolean {
  if (!start || !end) {
    return false;
  }

  const now = new Date().getTime() / 1000;
  return now >= start && now <= end;
}

export function getHourTimeWithSpan(spanTime: any, withSeconds: boolean = false): string {
  const time = new Date(new Date().getTime() + spanTime);
  const hh = padStart(time.getHours());
  const mm = padStart(time.getMinutes());
  const ss = padStart(time.getSeconds());

  if (withSeconds) {
    return `${hh}:${mm}:${ss}`;
  }

  return `${hh}:${mm}`;
}

export function milliseconds2HHMMSS(milliseconds: number): string {
  return new Date(milliseconds).toISOString().substr(11, 8);
}

export function formatTime(time: number, formatStr: string = 'YYYY-MM-DD'): string {
  const d = new Date(time);
  return formatStr
    .replace('YYYY', d.getFullYear().toString())
    .replace('MM', padStart(d.getMonth() + 1))
    .replace('DD', padStart(d.getDate()))
    .replace('HH', padStart(d.getHours()))
    .replace('mm', padStart(d.getMinutes()))
    .replace('ss', padStart(d.getSeconds()))
    .replace('SS', d.getMilliseconds() + '');
}

// 4500ms -> 00:04s
export function formatMSeconds(ms: number): string {
  const minutes = parseInt((ms % HOUR) / (1000 * 60) + '', 10);
  const seconds = Math.ceil((ms % MINUTE) / 1000);
  return [padStart(minutes), padStart(seconds)].join(':');
}

/*
 * 2020/02/10 xx:xx:xx to timestamp of 2020/02/10 00:00:00
 */
export function flatTimeToDay(time: number = Date.now()): number {
  const d = new Date(time);
  const year = d.getFullYear();
  const month = d.getMonth() + 1;
  const day = d.getDate();
  return new Date(`${year}/${month}/${day} 00:00:00`).getTime();
}

export function showTime(time: number, haveHms = true) {
  return formatTime(time, haveHms ? 'DD/MM/YYYY HH:mm:ss' : 'DD/MM/YYYY');
}

/**
 * Time to conversion time to the corresponding time zone
 * @param time
 * @param zone
 */
export function getZoneTime(_: number, zone: number) {
  return getTimeUTC() + zone * 60 * 60 * 1000;
}

/**
 * Get the current time UTC time
 */
export function getTimeUTC() {
  const d = new Date();
  return d.getTime() + d.getTimezoneOffset() * 60 * 1000;
}

// Pass the parameter unit seconds, settingzone sets the time zone where the parameter Time is located in the background
export function compareTimeWithUTC8(time: number): boolean {
  const localDatetime = new Date().getTime() / 1000;
  return localDatetime >= time;
}

/**
 *
 * @param date DD/MM/YYYY
 * @param time HH:mm
 */
export function getUnixTime(date: string, time: string): string {
  const reg = new RegExp(/^([0-9]{2})\/([0-9]{2})\/([0-9]{4})$/);
  const result = reg.exec(date);
  if (result) {
    return (new Date(`${result[3]}/${result[2]}/${result[1]} ${time}`).getTime() / 1000).toFixed(0);
  } else {
    return '';
  }
}

/**
 * Get the maximum number of days that month
 */
export function getMaxDayOfMonth(year: number, month: number) {
  const date = new Date(year, month + 1, 1, 0, 0, 0).getTime();
  return new Date(date - 1000).getDate();
}
