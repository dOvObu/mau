#ifndef DLOG_H
#define DLOG_H
#include <iostream>
#include <string>
#include <type_traits>

// From
// --=== baptiste-wicht.com/posts/2015/07/simulate-static_if-with-c11c14.html ===--

namespace static_if_detail {

	struct identity {
		template<typename T>
		T operator()(T&& x) const {
			return std::forward<T> (x);
		}
	};

	template<bool Cond>
	struct statement {
		template<typename F>
		void then (const F& f) {
			f (identity ());
		}

		template<typename F>
		void else_ (const F&) {}
	};

	template<>
	struct statement<false> {
		template<typename F>
		void then (const F&) {}

		template<typename F>
		void else_ (const F& f) {
			f (identity ());
		}
	};

} //end of namespace static_if_detail



template<bool Cond, typename F>
static_if_detail::statement<Cond> static_if (F const& f) {
	static_if_detail::statement<Cond> if_;
	if_.then (f);
	return if_;
}

template <typename T1>
void __dlog (T1 a) {
	static_if <(std::is_same<T1, std::wstring>::value)> ([&](auto f) {
		std::wcout << L", " << a << L" >" << std::endl;
	}).else_ ([&](auto f) {
		std::cout << ", " << a << " >" << std::endl;
	});
}

#ifdef __unix__
#else
	template<typename T1, typename... T>
	void __dlog (T1 a, T ...b) {

		std::cout << ", ";
		static_if <(std::is_same<T1, std::wstring>::value)> ([&](auto f) {
			std::wcout << a;
		}).else_ ([&](auto f) {
			std::cout << a;
		});

		static_if <(sizeof...(b) > 0)> ([&](auto f) {
			__dlog (b...);
		}).else_ ([&](auto f) {
			std::cout << " >" << std::endl;
		});
}
#endif


template <typename T1, typename... T>
void dlog (T1 a, T... b) {

	std::cout << "dlog: < ";
	static_if <(std::is_same<T1, std::wstring>::value)> ([&](auto f) {
		#ifdef __unix__
		#else
			std::wcout << a;
		#endif
	}).else_ ([&](auto f) {
		std::cout << a;
	});

	static_if <(sizeof...(b) > 0)> ([&](auto f) {
		#ifdef __unix__
		#else
			__dlog (b...);
		#endif
	}).else_ ([&](auto f) {
		std::cout << " >" << std::endl;
	});
}


#endif // DLOG_H