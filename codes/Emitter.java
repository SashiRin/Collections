package fb;

import java.util.*;

/**
 * 1. Support subscribing to events. sub = emitter.subscribe('click', callback);
 * sub2 = emitter.subscribe('click', callback2);
 * 
 * sub2.release();
 * 
 * 2. Support emitting events. emitter.emit('event_name'); This particular
 * example should lead to the `callback` above being invoked
 * 
 * Follow up: emitter.emit('event_name', 'foo', 'bar'); This particular example
 * should lead to the `callback` above being invoked with `foo` and `bar` as
 * parameters.
 * 
 * // 3. Support unsubscribing existing subscriptions by releasing them.
 * sub.release(); // `sub` is the reference returned by `subscribe` above
 */
public class Emitter {
	private static class Event {
		Runnable callback;
		List<Runnable> callbacks;

		public Event(Runnable callback, List<Runnable> callbacks) {
			this.callback = callback;
			this.callbacks = callbacks;
		}

		public void release() {
			Iterator<Runnable> iter = this.callbacks.iterator();
			while (iter.hasNext()) {
				if (this.callback == iter.next()) {
					iter.remove();
					break;
				}
			}
		}
	}

	private Map<String, List<Runnable>> callbacks;

	public Emitter() {
		this.callbacks = new HashMap<>();
	}

	public Event subscribe(String eventName, Runnable run) {
		List<Runnable> l = this.callbacks.computeIfAbsent(eventName, k -> new ArrayList<>());
		l.add(run);
		return new Event(run, l);
	}

	public void emit(String eventName) {
		for (Runnable run : this.callbacks.getOrDefault(eventName, Collections.emptyList())) {
			try {
				run.run();
			} catch (Exception ex) {
				// log error
			}
		}
	}

	public static void main(String[] args) {
		Emitter emitter = new Emitter();
		Event event1 = emitter.subscribe("click", () -> {
			System.out.println("click1");
		});
		Event event2 = emitter.subscribe("click", () -> {
			System.out.println("click2");
		});
		Event event3 = emitter.subscribe("click", () -> {
			System.out.println("exception");
			throw new IllegalArgumentException();
		});
		emitter.emit("click");
		System.out.println("1--------------------------");
		emitter.emit("clicks");
		System.out.println("2--------------------------");
		event2.release();
		emitter.emit("click");
		System.out.println("3--------------------------");
		event3.release();
		emitter.emit("click");
		System.out.println("4--------------------------");
		event1.release();
		emitter.emit("click");
		System.out.println("5--------------------------");
	}
}
